/**
 * @file comm.h
 * @author 满心欢喜
 * @brief 串行通信协议
 * @version 0.1
 * @date 2023-02-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __COMM_H_
#define __COMM_H_

/* @include */
#include <stdlib.h>

/* @typedef */
typedef unsigned char       comm_uint8;
typedef unsigned short int  comm_uint16;
typedef unsigned long int   comm_uint32;
typedef unsigned long long  comm_uint64;

typedef char                comm_int8;
typedef short int           comm_int16;
typedef long int            comm_int32;
typedef long long           comm_int64;

typedef comm_int8           comm_err;

/* @define */
#ifdef __CC_ARM                             /* ARM Compiler */
    #define __WEAK                          __weak
#elif defined (__IAR_SYSTEMS_ICC__)         /* for IAR Compiler */
    #define __WEAK                          __weak
#elif defined (__GNUC__)                    /* GNU GCC Compiler */
    #define __WEAK                          __attribute__((weak))
#elif defined (__ADSPBLACKFIN__)            /* for VisualDSP++ Compiler */
    #define __WEAK                          __attribute__((weak))
#else
    #error not supported tool chain
#endif

#define COMM_MALLOC                 malloc  // 空间申请接口
#define COMM_FREE                   free    // 空间释放接口

#define COMM_NULL                   NULL    // 空数据定义

#define COMM_HEAD_DATA              0x5AA5  // 帧起始数据

#define COMM_ERR_UNKNOW             -1      // 未知错误
#define COMM_ERR_SUCCESS            0       // 成功
#define COMM_ERR_NOTSPACE           1       // 空间不足
#define COMM_ERR_REPEAT             2       // 重复
#define COMM_ERR_DATAERROR          3       // 数据错误
#define COMM_ERR_NOTSTART           4       // 协议未启动
#define COMM_ERR_FIFOFULL           5       // 队列已满

#define COMM_STATE_INIT             0       // 初始状态
#define COMM_STATE_STOP             1       // 停止状态
#define COMM_STATE_READY            2       // 就绪状态

#define COMM_TXFIFO_SIZE            5       // 发送队列大小 （单位：sizeof(comm_item_t*)）
#define COMM_RXFIFO_SIZE            5       // 接收队列大小 （单位：sizeof(comm_item_t*)）
#define COMM_RXBYTEFIFO_SIZE        256     // 接收字节缓冲区大小 （单位：字节）

#define COMM_TAG_ACK                0       // 响应帧
#define COMM_TAG_REQUEST            1       // 请求帧
#define COMM_TAG_JOIN               2       // 加入帧
#define COMM_TAG_HB                 3       // 心跳帧

/* @struct */

/**
 * @brief tlv结构体
 * 
 */
typedef struct
{
    comm_uint8 tag;         // 帧类型
    comm_uint16 len;        // 帧长度
    comm_uint8* value;      // 帧数据
}comm_tlv_t;

/* @Function declarations */
comm_err comm_start(void);
comm_err comm_send(comm_tlv_t tlv);
void comm_handle(void);
comm_err comm_putBuf(comm_uint8* buf, comm_uint32 len);
comm_err comm_getByte(comm_uint8 byte);
comm_err comm_getBuf(comm_uint8* buf, comm_uint32 len);
comm_err comm_tick(comm_uint32 time);
comm_err comm_register(comm_uint8 tag, void (*callback)(comm_uint16 len, comm_uint8* value));

#endif
