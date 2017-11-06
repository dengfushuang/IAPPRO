
#include "ssp0.h"


static uint8 SSP0SendBuf[256];

extern uint32 SystemCoreClock;


uint8 SSP0WriteFull(DataQueue *Buf, QUEUE_DATA_TYPE Data, uint8 Mod)
{
    uint16 temp;

    Mod = Mod;

    temp = QueueSize((void *)Buf);
    while (temp <= QueueNData((void *)Buf))         /* 等待数据队列不满 */
    {
        
    }
    return QueueWrite((void *)Buf, Data);           /* 数据重新入队 */
}


uint8_t SSP0_Init(uint32 BPS)
{
    uint16 Fdiv;
	
	SSP_CFG_Type SSP0;
	LPC_SSP_TypeDef *SSP00;
	SSP0.ClockRate = 1000000;
	SSP0.Databit = 8;
	SSP0.CPHA = SSP_CPHA_FIRST;
	SSP0.CPOL = SSP_CPOL_HI;
	SSP0.FrameFormat = SSP_FRAME_SPI;
	SSP0.Mode = SSP_MASTER_MODE;
	SSP_Init(LPC_SSP0,&SSP0);
	
	SSP_Cmd(LPC_SSP0,ENABLE);
	
    //使能以SSP0控制器电源    
    LPC_SC->PCONP |= (1<<21);
    //Enable UART1 Pins.
    LPC_IOCON->P0_15 = 0x02;     
    LPC_IOCON->P0_16 = 0x02;
    LPC_IOCON->P0_17 = 0x02;     
    LPC_IOCON->P0_18 = 0x02; 
    
    LPC_SSP0->CR0 = 0x0087;
    LPC_SSP0->CR1 = 0x0002;	
    LPC_SSP0->CPSR = 0x0008;
    LPC_SSP0->IMSC = 0x0f;	

    NVIC_EnableIRQ(SSP0_IRQn);                 // Enable SSP0 interrupt 
	  if (QueueCreate((void *)SSP0SendBuf,
                     sizeof(SSP0SendBuf),
                     NULL,
                     (uint8 (*)())SSP0WriteFull) 
                     == NOT_OK)
    {
        return FALSE;
    }
	return TRUE;
}


void SSP0Putch(uint8 Data)
{
	uint8 temp;	
    QueueWrite((void *)SSP0SendBuf, Data);         /* 数据入队 */
    if ((LPC_SSP0->SR & 0x000000002) == 0)
    {                                               /* UART0发送保持寄存器空 */
        QueueRead(&temp, SSP0SendBuf);             /* 发送最初入队的数据 */
        LPC_SSP0->DR = temp;
    }
}

void SSP0Writech(uint8 ch)
{
	uint8 temp;	
    QueueWrite((void *)SSP0SendBuf,ch);         /* 数据入队 */
    if ((LPC_SSP0->SR & 0x000000002) == 0)
    {                                               /* UART0发送保持寄存器空 */
        QueueRead(&temp, SSP0SendBuf);             /* 发送最初入队的数据 */
        LPC_SSP0->DR = temp;
    }
	//if ((LPC_SSP0->SR & 0x000000001))
    //{                                               /* UART0发送保持寄存器空 */            /* 发送最初入队的数据 */
    //    LPC_SSP0->DR = ch;
    //}
}

void SSP0Put_str(uint8 *Data, uint16 NByte)
{
    while (NByte-- > 0)
    {
        SSP0Putch(*Data++);
    }
}


void SSP0Write_Str(uint8_t *Data)
{
    while (*Data != '\0' )
    {
        SSP0Putch(*Data++);
    }
}


uint8 SSP0Getch(void)
{
    uint8 err;
	
    while ((LPC_SSP0->SR & 0x00000004) == 0)                      /* 没有收到数据 */
    err = LPC_SSP0->DR;                       /* 读取收到的数据 */
    return err;
}


uint8 SSP0Get(void)
{
    uint8 err;
	
    while ((LPC_SSP0->SR & 0x00000004) == 0);              /* 没有收到数据 */
    err = LPC_SSP0->DR;                       /* 读取收到的数据 */
    return err;
}


void SSP0_IRQHandler (void) 
{
    uint8 SR, sendtemp ;
	if((SR & 0x02))
	{
		QueueRead(&sendtemp,SSP0SendBuf);
		LPC_SSP0->DR = sendtemp;
	}
	LPC_SSP0->ICR = 0x03;
}







