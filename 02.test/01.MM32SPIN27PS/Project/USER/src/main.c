/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				main
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.3 or MDK 5.24
* @Target core		MM32SPIN2XPs
* @Taobao			https://seekfree.taobao.com/
* @date				2020-11-23
********************************************************************************************************************/

#include "headfile.h"
#include "comm.h"
#include "list.h"

// *************************** 例程说明 ***************************
// 
// 测试需要准备逐飞科技MM32SPIIN27PS核心板一块
// 
// 调试下载需要准备逐飞科技CMSIS-DAP或Jlink调试下载器一个
// 
// 本例程是个空工程 用来给同学们移植使用
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project  clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
uint16 loop_count = 0;
uint8 io_input_state = 0;
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************

/**
 * @brief 协议字节流输出
 * 
 * @param buf 数据地址
 * @param len 数据长度
 */
comm_err comm_putBuf(comm_uint8* buf, comm_uint32 len)
{
    uart_putbuff(DEBUG_UART, buf, len);
    return COMM_ERR_SUCCESS;
}

int main(void)
{
    uint32 count = 0;
    board_init(true);
    uart_rx_irq(UART_1, 1);
    gpio_init(C0, GPO, 1, GPO_PUSH_PULL);
    gpio_init(C1, GPO, 1, GPO_PUSH_PULL);
    gpio_init(C2, GPO, 1, GPO_PUSH_PULL);
    gpio_init(C3, GPO, 1, GPO_PUSH_PULL);
    gpio_init(B15, GPI, 1, GPI_PULL_UP);
    comm_start();
    tim_interrupt_init_ms(TIM_1, 1, 0x00);
    tim_interrupt_init_ms(TIM_2, 5, 0x00);
    while(1)
    {
        if(gpio_get(B15) == 0)
        {
            gpio_toggle(C1);
            comm_tlv_t tlv = {.tag = 4, .len = sizeof(count), .value = (uint8*)&count};
            comm_send(tlv);
            count++;
            systick_delay_ms(150);
        }
    }
}
