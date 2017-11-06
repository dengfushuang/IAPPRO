#ifndef __INCLUDES_H
#define __INCLUDES_H


#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "LPC177x_8x.h"
#include "lpc177x_8x_ssp.h"
#include "LPC177x_8x_clkpwr.h"
#include "lpc177x_8x_iap.h"
#include "lpc177x_8x_crc.h"
#include "lpc177x_8x_systick.h"
#include "lpc177x_8x_gpio.h"


#include "iap_types.h"
#include "debug_frmwrk.h"
#include "lpc177x_8x_uart.h"
#include "cmd_process.h"


#define DEBUG_T 1               //调试

#define START_ADDR 0x00006000   //存储地址
#define PRO_SIZE 0x8000         //flash初始化长度
#define BUF_SIZE 4096           //程序缓存长度
#define REC_CMD_LEN 12          //串口接收命令数据长度

#define PIO_PORT_USED       (0)
#define PIO_PIN_USED        (21)
#define PIO_PIN_VALUE       (1 << PIO_PIN_USED)

extern int IAP_JUMP_APP_FLAG ;  //IAP跳转标志位，在startup_LPC17xx.s中判断
extern void runAPP_func(void);
#endif



