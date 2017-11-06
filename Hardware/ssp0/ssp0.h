
#ifndef __SSP0_H 
#define __SSP0_H 
#include "includes.h"
uint8 SSP0_Init(uint32 BPS);
void SSP0Putch(uint8 Data);   
void SSP0Put_str(uint8 *Data, uint16 NByte);
void SSP0Write_Str(uint8 *Data);

uint8 SSP0Getch(void);
uint8 SSP0Get(void);

void SSP0Writech(uint8 ch);

#endif

