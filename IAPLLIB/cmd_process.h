#ifndef __CMD_PROCESS_H
#define __CMD_PROCESS_H
#include "includes.h"

typedef enum {
UART_CMD_ERROR = 0,
UART_CMD_UPDATA,
UART_CMD_LOAD,
UART_CMD_RUN_APP
}UART_CMD;




typedef void(*APP_ENTRY)(void);


void updata_func(uint8* arry);
void runAPP_func(void);
void jump2APP_func(void);
void IAP_Cmd_Run(UART_CMD cmdid ,uint8 *arry);
#endif
