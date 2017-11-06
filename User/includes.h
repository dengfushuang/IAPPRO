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


#define DEBUG_T 1               //����

#define START_ADDR 0x00006000   //�洢��ַ
#define PRO_SIZE 0x8000         //flash��ʼ������
#define BUF_SIZE 4096           //���򻺴泤��
#define REC_CMD_LEN 12          //���ڽ����������ݳ���

#define PIO_PORT_USED       (0)
#define PIO_PIN_USED        (21)
#define PIO_PIN_VALUE       (1 << PIO_PIN_USED)

extern int IAP_JUMP_APP_FLAG ;  //IAP��ת��־λ����startup_LPC17xx.s���ж�
extern void runAPP_func(void);
#endif



