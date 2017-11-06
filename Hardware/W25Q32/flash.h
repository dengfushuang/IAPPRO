#ifndef __FLASH_H
#define __FLASH_H
#include "includes.h"

void Delayms(uint32 delay);
void W25Q32_Init(void);
Bool W25Q32_Busy(void);
void W25Q32_Write_Enable(uint8 fun);

void W25Q32_Erase_page(uint32 ADDR,uint16 cnt);

void W25Q32_Write(uint32 ADDR,void *pWriteBuf,uint8 cnt);
uint16 W25Q32_Read(uint32 ADDR,void *pReadBuf,uint16 cnt);

#endif

