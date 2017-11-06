#include "includes.h"
int IAP_JUMP_APP_FLAG = 0;  

/***********数据对齐方式****************/
#ifdef __IAR_SYSTEMS_ICC__
#pragma data_alignment=4
uint8_t code[BUF_SIZE];
#else
uint8_t __attribute__ ((aligned (4))) code[BUF_SIZE];   //程序缓存区
#endif

uint8 Recieve_cmd_arry[REC_CMD_LEN] = {0}; 
UART_CMD cmd_flag ;                           
static uint32 DelayCount = 200;               // 延时200*10ms

void SysTick_Handler(void)
{
	SYSTICK_ClearCounterFlag();
	if((DelayCount--)>0)
	{
		;
	}else                                    //上电延时两秒，时间一到跳转APP
	{
		SYSTICK_IntCmd(DISABLE);
	    SYSTICK_Cmd(DISABLE);
	    __disable_irq();
	    __disable_fault_irq();
	    __set_PRIMASK(1);
		runAPP_func();
	}
}
void runAPP_func(void)
{
    #ifdef DEBUG_T
	_DBG("\r\nroot:~$ ALL Data Programma OK !!!!.......");
	_DBG("\r\nroot:~$ Ready to Reset CPU!!!!!!!");
	_DBG("\r\nroot:~$ ");
	#endif
	IAP_JUMP_APP_FLAG = 1;          //APP跳转标志置位
	NVIC_SystemReset();             //cpu 复位
	
}
int  main()
{   uint32 i;
	uint8 ch;
	SystemInit();
	SYSTICK_InternalInit(10);       //系统定时器，延时10ms
	SYSTICK_IntCmd(ENABLE);
	SYSTICK_Cmd(ENABLE);
	debug_frmwrk_init();
    #ifdef DEBUG_T
    _DBG("\r\nroot:~$ ");
    #endif

	
	while(1)
	{
		cmd_flag = UART_CMD_ERROR;
	    while(1)
		{
			ch = UARTGetChar(LPC_UART0);
			if(ch == '\r')                 //上电延时期间输入'\r'则程序进入bootload
			{
				SYSTICK_IntCmd(DISABLE);
	            SYSTICK_Cmd(DISABLE);
				_DBG("\r\nroot:~$ ");
			}
			if(ch == '<')
			{
				break;
			}
		}
	    for(i = 0;i<REC_CMD_LEN;i++)
		{
			Recieve_cmd_arry[i] = UARTGetChar(LPC_UART0);
            #ifdef DEBUG_T
			_DBC(Recieve_cmd_arry[i]);
            #endif
			if(Recieve_cmd_arry[i] == '>')
			{
				if(strstr((char*)&Recieve_cmd_arry[0],"UPDATA") != NULL)         //进入程序更新
				{
					cmd_flag = UART_CMD_UPDATA;
					Recieve_cmd_arry[0]=1;
					break;
				}else if(strstr((char*)&Recieve_cmd_arry[0],"RUN_APP") != NULL)  //跳转到APP
				{
					cmd_flag = UART_CMD_RUN_APP;
					break;
				}
			}
		}
        IAP_Cmd_Run(cmd_flag,Recieve_cmd_arry);		
	}
    return 0;
}
