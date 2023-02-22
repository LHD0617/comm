/**
 * @file list.c
 * @author 满心欢喜
 * @brief 链表
 * @version 0.1
 * @date 2023-02-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* @include */
#include <stdlib.h>
#include <string.h>
#include "list.h"

/**
 * @brief 创建list
 * 
 * @param size 单位数据大小
 * @return list_cb_t* 对象指针 若为FIFO_NULL 则创建失败
 */
list_cb_t* list_create(list_uint8 size)
{
    list_cb_t* cb = (list_cb_t*)LIST_MALLOC(sizeof(list_cb_t));
    if(!cb) return LIST_NULL;
    cb->size = size;
    cb->len = 0;
    cb->next = LIST_NULL;
    return cb;
}

/**
 * @brief 删除链表
 * 
 * @param cb 对象指针
 */
void list_delete(list_cb_t* cb)
{
    list_clean(cb);
    LIST_FREE(cb);
    cb = LIST_NULL;
}

/**
 * @brief 表尾追加
 * 
 * @param cb 对象指针
 * @param data 数据指针
 * @return list_err 错误码
 */
list_err list_append(list_cb_t* cb, void* data)
{
    if(!cb) return LIST_ERROR_NOTEXIST;
    list_node_t* node = (list_node_t*)LIST_MALLOC(sizeof(list_node_t) + cb->size);
    if(!node) return LIST_ERROR_NOTSPACE;
    memcpy(node->data, data, cb->size);
    node->next = LIST_NULL;
    list_node_t* temp = cb->next;
    if(!temp)
    {
        cb->next = node;
    }
    else
    {
        while(temp->next) temp = temp->next;
        temp->next = node;
    }
    cb->len++;
    return LIST_ERROR_SUCCESS;
}

/**
 * @brief 列表插入
 * 
 * @param cb 对象指针
 * @param index 序号
 * @param data 数据指针
 * @return list_err 错误码
 */
list_err list_insert(list_cb_t* cb, list_uint32 index, void* data)
{
    if(!cb) return LIST_ERROR_NOTEXIST;
    if(cb->len > 0 && index >= cb->len) return LIST_ERROR_OUTRANGE;
    list_node_t* node = (list_node_t*)LIST_MALLOC(sizeof(list_node_t) + cb->size);
    if(!node) return LIST_ERROR_NOTSPACE;
    memcpy(node->data, data, cb->size);
    list_node_t* temp = cb->next;
    if(!index--) 
    {
        node->next = temp;
        cb->next = node;
        cb->len++;
        return LIST_ERROR_SUCCESS;
    }
    while(index--) temp = temp->next;
    node->next = temp->next;
    temp->next = node;
    cb->len++;
    return LIST_ERROR_SUCCESS;
}

/**
 * @brief 列表删除指定元素
 * 
 * @param cb 对象指针
 * @param index 序号
 * @return list_err 错误码
 */
list_err list_remove(list_cb_t* cb, list_uint32 index)
{
    if(!cb) return LIST_ERROR_NOTEXIST;
    if(index >= cb->len) return LIST_ERROR_OUTRANGE;
    list_node_t* node = cb->next;
    if(!index--)
    {
        cb->next = node->next;
        LIST_FREE(node);
        cb->len--;
        return LIST_ERROR_SUCCESS;
    }
    while(index--) node = node->next;
    list_node_t* temp = node->next;
    node->next = temp->next;
    LIST_FREE(temp);
    cb->len--;
    return LIST_ERROR_SUCCESS;
}

/**
 * @brief 列表清空
 * 
 * @param cb 对象指针
 * @return list_err 错误码
 */
list_err list_clean(list_cb_t* cb)
{
    if(!cb) return LIST_ERROR_NOTEXIST;
    list_node_t* node = cb->next;
    cb->next = LIST_NULL;
    cb->len = 0;
    list_node_t* temp = LIST_NULL;
    while(node)
    {
        temp = node->next;
		LIST_FREE(node);
		node = temp;
    }
    return LIST_ERROR_SUCCESS;
}

/**
 * @brief 元素修改
 * 
 * @param cb 对象指针
 * @param index 序号
 * @param data 数据
 * @return list_err 错误码
 */
list_err list_revise(list_cb_t* cb, list_uint32 index, void* data)
{
    if(!cb) return LIST_ERROR_NOTEXIST;
    if(index >= cb->len) return LIST_ERROR_OUTRANGE;
    list_node_t* node = cb->next;
    while(index--) node = node->next;
    memcpy(node->data, data, cb->size);
    return LIST_ERROR_SUCCESS;
}

/**
 * @brief 元素查询
 * 
 * @param cb 对象指针
 * @param index 序号
 * @param data 数据输出地址
 * @return list_err 错误码
 */
list_err list_query(list_cb_t* cb, list_uint32 index, void* data)
{
    if(!cb) return LIST_ERROR_NOTEXIST;
    if(index >= cb->len) return LIST_ERROR_OUTRANGE;
    list_node_t* node = cb->next;
    while(index--) node = node->next;
    memcpy(data, node->data, cb->size);
    return LIST_ERROR_SUCCESS;
}

/**
 * @brief 获取列表长度
 * 
 * @param cb 对象指针
 * @return list_uint32 列表长度
 */
list_uint32 list_count(list_cb_t* cb)
{
    if(!cb) return 0;
    return cb->len;
}
