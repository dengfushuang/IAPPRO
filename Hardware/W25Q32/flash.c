#include "flash.h"
void Delayms(uint32 delay)
{
	uint32 i,j;
	for(i = 0 ;i < delay ;i ++)
	 for(j=600000;j > 0 ;j --);
}
void SSP_Tx(LPC_SSP_TypeDef *ssp,uint8 dat)
{
	uint16 a=0;
	a |=dat;
	while(LPC_SSP0->SR & (1 << 4)){;}
	
	SSP_SendData(LPC_SSP0,a);

}
void W25Q32_Init()
{
	SSP_CFG_Type SSP0;
	
	LPC_SC->PCONP |= (1<<21);
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCSSP0,ENABLE);
    //Enable UART1 Pins.
    LPC_IOCON->P0_15 = 0x0A;     
    LPC_IOCON->P0_16 = 0x0A;
    LPC_IOCON->P0_17 = 0x0A;     
    LPC_IOCON->P0_18 = 0x0A;
	
	SSP0.ClockRate = 1000000;
	SSP0.Databit = 8;
	SSP0.CPHA = SSP_CPHA_FIRST;
	SSP0.CPOL = SSP_CPOL_LO;
	SSP0.FrameFormat = SSP_FRAME_SPI;
	SSP0.Mode = SSP_MASTER_MODE;
	SSP_Init(LPC_SSP0,&SSP0);
	
	SSP_Cmd(LPC_SSP0,ENABLE);
	SSP_Tx(LPC_SSP0,0x98);
}
void W25Q32_Write_Enable(uint8 fun)
{
	SSP_Tx(LPC_SSP0,0x06);
	
	Delayms(10);
}
Bool isW25Q32_Busy()
{
	uint8 statu;
	SSP_Tx(LPC_SSP0,0x0005);
    statu = SSP_ReceiveData(LPC_SSP0);
	if(statu & 0x01)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void W25Q32_Erase_page(uint32 ADDR,uint16 cnt)
{
	uint16 i;
	W25Q32_Write_Enable(ENABLE);
	while(isW25Q32_Busy()==TRUE);
	if(cnt == 0 )
	{
		SSP_Tx(LPC_SSP0,0xc7);
	}else
	{
		for(i = 0 ;i < cnt ; i ++)
		{
			
			while(isW25Q32_Busy()==TRUE){;}
		    SSP_Tx(LPC_SSP0,0x02);
			SSP_Tx(LPC_SSP0,(uint8)(ADDR)>>24);
			SSP_Tx(LPC_SSP0,(uint8)(ADDR)>>16);
			SSP_Tx(LPC_SSP0,(uint8)(ADDR));
		}
	}
	while(isW25Q32_Busy()==TRUE);
}
void W25Q32_Write(uint32 ADDR,void *pWriteBuf,uint8 cnt)
{
	SSP_DATA_SETUP_Type data;
	data.tx_data = pWriteBuf;
	data.rx_data = NULL;
	data.length = cnt;
	W25Q32_Write_Enable(ENABLE);
	while(isW25Q32_Busy()==TRUE){Delayms(5);}
	 SSP_ReadWrite(LPC_SSP0,&data,SSP_TRANSFER_POLLING);
	while(isW25Q32_Busy()==TRUE){Delayms(5);}
}
uint16 W25Q32_Read(uint32 ADDR,void *pReadBuf,uint16 cnt)
{
	uint16 i;
	SSP_DATA_SETUP_Type data;
	data.rx_data = pReadBuf;
	data.tx_data = NULL;
	data.length = cnt;
	while(isW25Q32_Busy()==TRUE){Delayms(5);}
	 i = SSP_ReadWrite(LPC_SSP0,&data,SSP_TRANSFER_POLLING);
	while(isW25Q32_Busy()==TRUE){Delayms(5);}
	SSP_SendData(LPC_SSP0,0x66);
	SSP_SendData(LPC_SSP0,0x99);
	return i;
}

