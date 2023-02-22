/**
 * @file list.h
 * @author 满心欢喜
 * @brief 链表
 * @version 0.1
 * @date 2023-02-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __LIST_H_
#define __LIST_H_

/* @typedef */
typedef unsigned char       list_uint8;
typedef unsigned short int  list_uint16;
typedef unsigned long int   list_uint32;
typedef unsigned long long  list_uint64;

typedef char                list_int8;
typedef short int           list_int16;
typedef long int            list_int32;
typedef long long           list_int64;

typedef list_int8           list_err;

/* @define */
#define         LIST_MALLOC                 malloc      // 空间申请接口
#define         LIST_FREE                   free        // 空间释放接口

#define         LIST_NULL                   NULL        // 空类型
#define         LIST_ERROR_SUCCESS          0x00        // 成功
#define         LIST_ERROR_NOTSPACE         0x01        // 空间不足
#define         LIST_ERROR_NOTEXIST         0x02        // 列表不存在
#define         LIST_ERROR_OUTRANGE         0x03        // 索引超出范围

/* @struct */
#pragma pack(1) // 单字节对齐

/**
 * @brief 节点结构体
 * 
 */
typedef struct list_node_t
{
    struct list_node_t* next;   // 指针域
    list_uint8 data[];          // 数据域
}list_node_t;

/**
 * @brief 链表控制块
 * 
 */
typedef struct
{
    list_uint8 size;            // 单位节点数据大小
    list_uint32 len;            // 链表长度
    list_node_t* next;          // 头指针
}list_cb_t;

#pragma pack() // 恢复默认字节对齐

/* @Function declaration */
list_cb_t* list_create(list_uint8 size);
void list_delete(list_cb_t* cb);
list_err list_append(list_cb_t* cb, void* data);
list_err list_insert(list_cb_t* cb, list_uint32 index, void* data);
list_err list_remove(list_cb_t* cb, list_uint32 index);
list_err list_clean(list_cb_t* cb);
list_err list_revise(list_cb_t* cb, list_uint32 index, void* data);
list_err list_query(list_cb_t* cb, list_uint32 index, void* data);
list_uint32 list_count(list_cb_t* cb);

#endif
