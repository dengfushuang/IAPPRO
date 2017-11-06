#include "cmd_process.h"

static uint8 flag = 0;
extern uint8_t code[];
void updata_func(uint8* arry)
{
	uint8 * ptr;
	uint8 temp02;
	IAP_STATUS_CODE statuflag;
	uint32 i;
	uint32_t results[4];
	uint32 start_addr,end_addr;
	uint32 Rcv_checksum =0;
	uint32 checksum = 0;
	
	
	start_addr = GetSecNum(START_ADDR);
	end_addr = GetSecNum(START_ADDR+PRO_SIZE);
	CRC_Init(CRC_POLY_CRC32);
	if(arry[0]==1)
	{   
            #ifdef DEBUG_T
		    _DBG("\r\nroot:~$ READY.......");
		    _DBG("\r\nroot:~$ ");
            #endif
			for(i = 0 ;i < 4096; i++)
			{
				code[i]=UARTGetChar(LPC_UART0);
				if(i > 1)
				{
					if(i > 5)
					{
						temp02 = code[i-5];
					}
				}
				if(code[i] == '>' && temp02 == '<')
				{
					break;
					
				}
				
			 }
            #ifdef DEBUG_T
		    _DBG("\r\nroot:~$ load data OK.......");
		    _DBG("\r\nroot:~$ ");
            #endif
	 }
	    if(code[i] == '>' && temp02 == '<')
		{
			checksum |= code[i-4];
			checksum <<=8;
			checksum |= code[i-3];
			checksum <<=8;
			checksum |= code[i-2];
			checksum <<=8;
			checksum |= code[i-1];
			Rcv_checksum = CRC_CalcBlockChecksum(code,(i-5),CRC_WR_8BIT);
			if(Rcv_checksum == checksum)
			{
				
				#ifdef DEBUG_T
				_DBG("\r\nroot:~$ CRC Check Success !!!!.......");
				_DBG("\r\nroot:~$ ");
				#endif
				flag = 1;
			}
			else
			{
				
				#ifdef DEBUG_T
				_DBG("\r\nroot:~$ CRC Check false !!!!.......");
				_DBG("\r\nroot:~$ ");
				#endif
				flag = 0;
			}
			
		}
		else{
		    flag = 0;
		}
	    
	    if(flag == 1)
		{
			flag = 0;
			statuflag = ReadPartID(results);
			if(statuflag == CMD_SUCCESS)
			{
				
				statuflag = ReadDeviceSerialNum(results);
				if(statuflag == CMD_SUCCESS)
				{
					 statuflag = PrepareSector(start_addr,end_addr);
					 statuflag = EraseSector(start_addr,end_addr);
					 if(statuflag == CMD_SUCCESS)
					 {
						 statuflag = BlankCheckSector(start_addr, end_addr,&results[0], &results[1]);
						 if(statuflag == CMD_SUCCESS)
						 {
							 for(i = 0 ;i < (PRO_SIZE/BUF_SIZE) ;i++)
							 {
								 ptr = (uint8_t*)(START_ADDR+ i*BUF_SIZE);
								 statuflag = PrepareSector(start_addr,end_addr);
								 if(statuflag == CMD_SUCCESS)
								 {
									 statuflag =  CopyRAM2Flash(ptr,(uint8_t*)(&code[i*BUF_SIZE]),IAP_WRITE_4096);
									 if(statuflag != CMD_SUCCESS)
									 {
										  #ifdef DEBUG_T
										  _DBG("\r\nroot:~$ Programma ERROR !!!!.......");
										  _DBG("\r\nroot:~$ ");
										  #endif
									 }
									 else
									 {
										   #ifdef DEBUG_T
										   _DBG("\r\nroot:~$ Program data to flash Success !!!!.......");
										   _DBG("\r\nroot:~$ ");
										   #endif         
										   flag = 1;
									 }
								 }
								 else
								 {
									 #ifdef DEBUG_T
									 _DBG("\r\nroot:~$ PrepareSector ERROR !!!!.......");
							
									 #endif
								 }
								 
							  }
						 }
						 else
						 {
							  #ifdef DEBUG_T
							  _DBG("\r\nroot:~$ BlankCheckSector ERROR !!!!.......");
							
							  #endif 
							 while(1);
						 }
					 }
					 else
					 {
						 #ifdef DEBUG_T
						 _DBG("\r\nroot:~$ EraseSector ERROR !!!!.......");
						 #endif 
						 while(1);
					 }					 
				}
				else
				{
					#ifdef DEBUG_T
					_DBG("\r\nroot:~$ ReadDeviceSerialNum ERROR !!!!.......");
					#endif 
					while(1);
				}			
			}
			else
			{
				#ifdef DEBUG_T
				_DBG("\r\nroot:~$ ReadPartID ERROR !!!!.......");
				#endif 
				flag = 0;
				while(1);
			}
		}
		
				
//        for ( i = 0; i < PRO_SIZE/BUF_SIZE; i++ )
//		{
//			ptr = (uint8_t*)(START_ADDR + i*BUF_SIZE);
//			statuflag =  Compare(ptr,(uint8_t*)(&code[i*BUF_SIZE]),BUF_SIZE);
//			if(statuflag != CMD_SUCCESS)
//			{
//				_DBG("Compare memory failed with code is ");_DBD(statuflag);_DBG_("");
//				while(1);
//			}
//			else
//			{
//				#ifdef DEBUG_T
//				_DBG("\r\nroot:~$ check Success !!!!.......");
//				_DBG("\r\nroot:~$ ");
//				flag = 1;
//				#endif
//			}
//		 }			
		  
             
}
void Delayms(uint32 delay)
{
	uint32 i,j;
	for(i = 0 ;i < delay ;i ++)
	 for(j=600000;j > 0 ;j --);
}

void IAP_Cmd_Run(UART_CMD cmdid ,uint8 *arry)
{
	switch(cmdid)
	{
		case UART_CMD_ERROR:break;
		
		case UART_CMD_UPDATA:{
				updata_func(arry);
				if(flag==0)
				{
					break;
				}
				else
				{
					runAPP_func();break;
				}
		    }
		case UART_CMD_RUN_APP:runAPP_func();break;
		
		default:break;			
	}	
}
