/**
 * @file comm.c
 * @author 满心欢喜
 * @brief 串行通信协议
 * @version 0.1
 * @date 2023-02-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* @include */
#include <string.h>
#include "comm.h"
#include "fifo.h"
#include "list.h"

/* @struct */
#pragma pack(1) // 单字节对齐

/**
 * @brief tlv结构体
 * 该结构体定义为线性结构仅作为内部使用
 * 
 */
typedef struct
{
    comm_uint8 tag;                 // 帧类型
    comm_uint16 len;                // 帧长度
    comm_uint8 value[];             // 帧数据
}_comm_tlv_t;

/**
 * @brief 数据帧结构体
 * 
 */
typedef struct
{
    comm_uint16 head;               // 起始标识
    comm_uint8 hcrc;                // 帧头校验
    comm_uint8 dcrc;                // 数据校验
    comm_uint32 sn;                 // 帧流水编号
    comm_uint32 len;                // 数据长度
    _comm_tlv_t tlv[];              // tlv结构体
}comm_item_t;

/**
 * @brief 回调函数结构体
 * 
 */
typedef struct
{
    comm_uint8 tag;
    void (*callback)(comm_uint16 len, comm_uint8* value);
}comm_callback_t;

/**
 * @brief ACK帧数据结构体
 * 
 */
typedef struct
{
    comm_uint32 sn;
    comm_uint8 err;
}_ack_t;

/**
 * @brief 协议控制块结构体
 * 
 */
typedef struct
{
    comm_uint8 state;               // 协议运行状态
    fifo_cb_t* tx_fifo;             // 发送队列
    fifo_cb_t* rx_bytefifo;         // 接收字节缓冲区
    comm_uint32 tx_sn;              // 发送流水编号
    comm_uint32 rx_sn;              // 上次接收流水编号
    comm_uint64 time;               // 时间戳
    comm_uint64 tx_time;            // 发送时间戳
    comm_uint64 rx_time;            // 接收时间戳
    comm_item_t* tx_item;           // 当前发送帧指针
    comm_item_t* rx_item;           // 当前接收帧指针
    comm_uint8 repeat;              // 重发次数
    comm_uint32 rx_len;             // 当前接收长度
    list_cb_t* callback_list;       // 回调函数列表
}comm_cb_t;

#pragma pack() // 恢复默认字节对齐

/* @global */
static comm_cb_t comm_cb =  // 协议控制块
{
    .state = COMM_STATE_INIT,
    .tx_fifo = COMM_NULL,
    .rx_bytefifo = COMM_NULL,
    .tx_sn = 0,
    .rx_sn = 0xffffffff,
    .time = 0,
    .tx_time = 0,
    .rx_time = 0,
    .tx_item = COMM_NULL,
    .rx_item = COMM_NULL,
    .repeat = 0,
    .rx_len = 0,
    .callback_list = COMM_NULL,
};

/**
 * @brief 查表法计算CRC值，按照多项式 X^8+X^2+X^1+1 生成
 * 
 */
static const comm_uint8 _crc8Table[256] =
{
    0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15, 0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
    0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65, 0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
    0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5, 0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
    0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85, 0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
    0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2, 0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
    0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2, 0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
    0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32, 0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
    0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42, 0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
    0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C, 0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
    0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC, 0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
    0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C, 0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
    0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C, 0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
    0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B, 0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
    0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B, 0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
    0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB, 0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
    0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB, 0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};

/* @Function declarations */
static comm_err _sendFrame(comm_item_t* item);
static comm_err _sendAck(comm_uint32 sn, comm_uint8 err);
static comm_uint8 _crc8(comm_uint8 *data, comm_uint32 len);
static void _ackCallback(comm_uint16 len, comm_uint8* value);

/**
 * @brief 启动串行通信协议
 * 
 * @return comm_err 错误码
 */
comm_err comm_start(void)
{
    if(comm_cb.state == COMM_STATE_INIT)
    {
        comm_cb.tx_fifo = fifo_create(COMM_TXFIFO_SIZE * sizeof(comm_item_t*));
        if(!comm_cb.tx_fifo) goto NOTSPACE;
        comm_cb.rx_bytefifo = fifo_create(COMM_RXBYTEFIFO_SIZE);
        if(!comm_cb.rx_bytefifo) goto NOTSPACE;
        comm_cb.callback_list = list_create(sizeof(comm_callback_t));
        if(!comm_cb.callback_list) goto NOTSPACE;
        comm_callback_t callback = {.tag = COMM_TAG_ACK, .callback = _ackCallback};
        if(list_append(comm_cb.callback_list, &callback)) goto NOTSPACE;
        comm_cb.state = COMM_STATE_READY;
        return COMM_ERR_SUCCESS;
    }
    return COMM_ERR_REPEAT;

NOTSPACE:
    fifo_delete(comm_cb.tx_fifo);
    fifo_delete(comm_cb.rx_bytefifo);
    list_delete(comm_cb.callback_list);
    return COMM_ERR_NOTSPACE;
}

/**
 * @brief 发送数据
 * 
 * @param tlv 数据tlv
 * @return comm_err 
 */
comm_err comm_send(comm_tlv_t tlv)
{
    if(comm_cb.state == COMM_STATE_INIT) return COMM_ERR_NOTSTART;
    if(!(fifo_getAvailable(comm_cb.tx_fifo) >= sizeof(comm_item_t*))) return COMM_ERR_FIFOFULL;
    comm_item_t* item = (comm_item_t*)COMM_MALLOC(sizeof(comm_item_t) + sizeof(_comm_tlv_t) + tlv.len);
    if(!item) return COMM_ERR_NOTSPACE;
    memcpy(item->tlv->value, tlv.value, tlv.len);
    item->tlv->len = tlv.len;
    item->tlv->tag = tlv.tag;
    item->len = sizeof(_comm_tlv_t) + tlv.len;
    item->sn = comm_cb.tx_sn++;
    item->dcrc = _crc8((comm_uint8*)&item->tlv, item->len);
    item->hcrc = _crc8(&item->dcrc, (comm_uint8*)item->tlv - &item->dcrc);
    item->head = COMM_HEAD_DATA;
    fifo_err err = fifo_pushBuf(comm_cb.tx_fifo, (comm_uint8*)&item, sizeof(item));
    if(err == FIFO_ERROR_SUCCESS) return COMM_ERR_SUCCESS;
    COMM_FREE(item);
    return COMM_ERR_UNKNOW;
}

/**
 * @brief 协议运行处理
 * 
 */
void comm_handle(void)
{
    /* 发送数据 */
    if(!comm_cb.tx_item)
    {
        fifo_err err = fifo_popBuf(comm_cb.tx_fifo, (comm_uint8*)&comm_cb.tx_item, sizeof(comm_cb.tx_item));
        if(err == FIFO_ERROR_SUCCESS)
        {
            _sendFrame(comm_cb.tx_item);
            comm_cb.tx_time = comm_cb.time;
            comm_cb.repeat = 1;
        }
    }
    else
    {
        if(comm_cb.time - comm_cb.tx_time >= COMM_TX_TIMEOUT)
        {
            _sendFrame(comm_cb.tx_item);
            comm_cb.tx_time = comm_cb.time;
            comm_cb.repeat++;
            if(comm_cb.repeat >= COMM_TX_REPEAT)
            {
                COMM_FREE(comm_cb.tx_item);
                comm_cb.tx_item = COMM_NULL;
            }
        }
    }
    /* 接收数据 */
    if(!comm_cb.rx_item)
    {
        comm_item_t item;
        fifo_err err = fifo_popBuf(comm_cb.rx_bytefifo, (comm_uint8*)&item, sizeof(comm_item_t));
        if(err == FIFO_ERROR_SUCCESS)
        {
            if(item.head == COMM_HEAD_DATA && item.hcrc == _crc8(&item.dcrc, (comm_uint8*)item.tlv - &item.dcrc))
            {
                comm_cb.rx_item = (comm_item_t*)COMM_MALLOC(sizeof(comm_item_t) + item.len);
                if(comm_cb.rx_item) *comm_cb.rx_item = item;
                comm_cb.rx_len = 0;
                comm_cb.rx_time = comm_cb.time;
            }
            else
            {
                fifo_clean(comm_cb.rx_bytefifo);
                COMM_FREE(comm_cb.rx_item);
                comm_cb.rx_item = COMM_NULL;
            }
        }
    }
    if(comm_cb.rx_item)
    {
        if(comm_cb.time - comm_cb.rx_time >= COMM_RX_TIMEOUT)
        {
            _sendAck(comm_cb.rx_item->sn, COMM_ACK_ERR_TIMEOUT);
            COMM_FREE(comm_cb.rx_item);
            comm_cb.rx_item = COMM_NULL;
        }
        else
        {
            comm_uint32 len = fifo_getUsed(comm_cb.rx_bytefifo);
            if(comm_cb.rx_len + len > comm_cb.rx_item->len) len = comm_cb.rx_item->len - comm_cb.rx_len;
            fifo_err err = fifo_popBuf(comm_cb.rx_bytefifo, (comm_uint8*)(comm_cb.rx_item->tlv) + comm_cb.rx_len, len);
            if(err == FIFO_ERROR_SUCCESS)
            {
                comm_cb.rx_len += len;
                comm_cb.rx_time = comm_cb.time;
            }
            if(comm_cb.rx_len == comm_cb.rx_item->len)
            {
                if(comm_cb.rx_item->dcrc == _crc8((comm_uint8*)comm_cb.rx_item->tlv, comm_cb.rx_item->len))
                {
                    if(comm_cb.rx_item->tlv->tag != COMM_TAG_ACK)
                    {
                        if(comm_cb.rx_item->sn == comm_cb.rx_sn)
                        {
                            _sendAck(comm_cb.rx_item->sn, COMM_ACK_ERR_REPEAT);
                        }
                        else
                        {
                            _sendAck(comm_cb.rx_item->sn, COMM_ACK_ERR_SUCCESS);
                            comm_cb.rx_sn = comm_cb.rx_item->sn;
                            comm_callback_t callback;
                            for(comm_uint32 i = 0; i < list_count(comm_cb.callback_list); i++)
                            {
                                if(!list_query(comm_cb.callback_list, i, &callback))
                                {
                                    if(callback.tag == comm_cb.rx_item->tlv->tag)
                                    {
                                        callback.callback(comm_cb.rx_item->tlv->len, comm_cb.rx_item->tlv->value);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        comm_callback_t callback;
                        for(comm_uint32 i = 0; i < list_count(comm_cb.callback_list); i++)
                        {
                            if(!list_query(comm_cb.callback_list, i, &callback))
                            {
                                if(callback.tag == COMM_TAG_ACK)
                                {
                                    callback.callback(comm_cb.rx_item->tlv->len, comm_cb.rx_item->tlv->value);
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(comm_cb.rx_item->tlv->tag != COMM_TAG_ACK)
                    {
                        _sendAck(comm_cb.rx_item->sn, COMM_ACK_ERR_CRC);
                    }
                    else
                    {
                        if(comm_cb.repeat >= COMM_TX_REPEAT)
                        {
                            COMM_FREE(comm_cb.tx_item);
                            comm_cb.tx_item = COMM_NULL;
                        }
                        else
                        {
                            _sendFrame(comm_cb.tx_item);
                            comm_cb.tx_time = comm_cb.time;
                            comm_cb.repeat++;
                        }
                    }
                }
                COMM_FREE(comm_cb.rx_item);
                comm_cb.rx_item = COMM_NULL;
            }
        }
    }
}

/**
 * @brief 协议字节流输出
 * 
 * @param buf 数据地址
 * @param len 数据长度
 */
__WEAK comm_err comm_putBuf(comm_uint8* buf, comm_uint32 len)
{
    /* 此函数为虚函数需要用户在使用时重新实现 */
    return COMM_ERR_SUCCESS;
}

/**
 * @brief 协议字节输入
 * 
 * @return comm_err 错误码
 */
comm_err comm_getByte(comm_uint8 byte)
{
    if(comm_cb.state == COMM_STATE_INIT) return COMM_ERR_NOTSTART;
    fifo_err err = fifo_pushByte(comm_cb.rx_bytefifo, byte);
    if(err == FIFO_ERROR_SUCCESS) return COMM_ERR_SUCCESS;
    else return COMM_ERR_UNKNOW;
}

/**
 * @brief 协议字节流输入
 * 
 * @param buf 字节流地址
 * @param len 字节流长度
 * @return comm_err 错误码
 */
comm_err comm_getBuf(comm_uint8* buf, comm_uint32 len)
{
    if(comm_cb.state == COMM_STATE_INIT) return COMM_ERR_NOTSTART;
    fifo_err err = fifo_pushBuf(comm_cb.rx_bytefifo, buf, len);
    if(err == FIFO_ERROR_SUCCESS) return COMM_ERR_SUCCESS;
    else return COMM_ERR_UNKNOW;
}

/**
 * @brief 协议心跳输入
 * 
 * @param time 心跳时间 （单位：ms）
 * @return comm_err 错误码
 */
comm_err comm_tick(comm_uint32 time)
{
    if(comm_cb.state == COMM_STATE_INIT) return COMM_ERR_NOTSTART;
    comm_cb.time += time;
    return COMM_ERR_SUCCESS;
}

/**
 * @brief 注册回调函数
 * 
 * @param tag 数据标签
 * @param callback 回调函数
 * @return comm_err 错误码
 */
comm_err comm_register(comm_uint8 tag, void (*callback)(comm_uint16 len, comm_uint8* value))
{
    if(comm_cb.state == COMM_STATE_INIT) return COMM_ERR_NOTSTART;
    comm_callback_t temp;
    for(comm_uint32 i = 0; i < list_count(comm_cb.callback_list); i++)
    {
        if(list_query(comm_cb.callback_list, i, &temp)) return COMM_ERR_UNKNOW;
        if(temp.tag == tag) return COMM_ERR_REPEAT;
    }
    temp.tag = tag;
    temp.callback = callback;
    list_err err = list_append(comm_cb.callback_list, &temp);
    if(err == LIST_ERROR_SUCCESS) return COMM_ERR_SUCCESS;
    if(err == LIST_ERROR_NOTSPACE) return COMM_ERR_NOTSPACE;
    return COMM_ERR_UNKNOW;
}

/**
 * @brief 发送数据帧
 * 
 * @param item 数据帧结构体
 */
static comm_err _sendFrame(comm_item_t* item)
{
    if(!item) return COMM_ERR_DATAERROR;
    if(comm_putBuf((comm_uint8*)item, sizeof(comm_item_t) + sizeof(_comm_tlv_t) + item->tlv->len) == COMM_ERR_SUCCESS)
        return COMM_ERR_SUCCESS;
    else
        return COMM_ERR_UNKNOW;
}

/**
 * @brief 发送响应帧
 * 
 * @param sn 帧流水编号
 * @param err 错误码
 * @return comm_err 错误码
 */
static comm_err _sendAck(comm_uint32 sn, comm_uint8 err)
{
    if(comm_cb.state == COMM_STATE_INIT) return COMM_ERR_NOTSTART;
    _ack_t ack = {.sn = sn, .err = err};
    comm_item_t* item = (comm_item_t*)COMM_MALLOC(sizeof(comm_item_t) + sizeof(_comm_tlv_t) + sizeof(_ack_t));
    if(!item) return COMM_ERR_NOTSPACE;
    item->tlv->tag = COMM_TAG_ACK;
    item->tlv->len = sizeof(_ack_t);
    memcpy(item->tlv->value, &ack, item->tlv->len);
    item->len = sizeof(_comm_tlv_t) + item->tlv->len;
    item->sn = comm_cb.tx_sn++;
    item->dcrc = _crc8((comm_uint8*)&item->tlv, item->len);
    item->hcrc = _crc8(&item->dcrc, (comm_uint8*)item->tlv - &item->dcrc);
    item->head = COMM_HEAD_DATA;
    comm_err temp = _sendFrame(item);
    COMM_FREE(item);
    return temp;
}

/**
 * @brief 计算crc8
 * 
 * @param data 数据指针
 * @param len 数据长度
 * @return comm_uint8 crc8计算结果
 */
static comm_uint8 _crc8(comm_uint8 *data, comm_uint32 len)
{
    comm_uint8 crc8 = 0;
    while(len--)
    {
        crc8 = crc8 ^ (*data++);
        crc8 = _crc8Table[crc8];
    }
    return crc8;
}

/**
 * @brief 响应帧回调函数
 * 
 * @param len 数据长度
 * @param value 数据地址
 */
static void _ackCallback(comm_uint16 len, comm_uint8* value)
{
    if(len != sizeof(_ack_t)) return;
    _ack_t ack = *(_ack_t*)value;
    if(comm_cb.tx_item && ack.sn == comm_cb.tx_item->sn)
    {
        switch(ack.err)
        {
            case COMM_ACK_ERR_SUCCESS:
            {
                COMM_FREE(comm_cb.tx_item);
                comm_cb.tx_item = COMM_NULL;
                break;
            }
            case COMM_ACK_ERR_CRC:
            {
                if(comm_cb.repeat >= COMM_TX_REPEAT)
                {
                    COMM_FREE(comm_cb.tx_item);
                    comm_cb.tx_item = COMM_NULL;
                }
                else
                {
                    _sendFrame(comm_cb.tx_item);
                    comm_cb.tx_time = comm_cb.time;
                    comm_cb.repeat++;
                }
                break;
            }
            case COMM_ACK_ERR_TIMEOUT:
            {
                COMM_FREE(comm_cb.tx_item);
                comm_cb.tx_item = COMM_NULL;
                break;
            }
            case COMM_ACK_ERR_REPEAT:
            {
                COMM_FREE(comm_cb.tx_item);
                comm_cb.tx_item = COMM_NULL;
                break;
            }
            default:
            {
                COMM_FREE(comm_cb.tx_item);
                comm_cb.tx_item = COMM_NULL;
                break;
            }
        }
    }
}
