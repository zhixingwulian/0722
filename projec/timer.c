/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Jan/21/2019                                                                                   */
/***********************************************************************************************************/

/************************************************************************************************************/
/*  File Function: MS51 UART0 initial demo code                                                             */
/************************************************************************************************************/
#include "MS51.H"

bit receiveFlag;
int LedFlag = 0;
char a[11] = 0;
UINT32 receive[11] = 0;
int j = 0;
int T = 0;
char flag =0;
/************************************************************************************************************

************************************************************************************************************/
void Serial_ISR (void) interrupt 4 
{
		
    if (RI)
    {   
      receiveFlag = 1;
			LedFlag++;
      receive[j] = SBUF;
			j++;
      clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }
    if (TI)
    {       
        clr_SCON_TI;                                       // Clear TI (Transmit Interrupt).
    }

}



/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
		int i = 0;
    P12_PUSHPULL_MODE;

    ENABLE_TIMER1_MODE0;                           /* Timer 0 mode configuration */
    MODIFY_HIRC_24();
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;

 //   ENABLE_TIMER0_INTERRUPT;                       /* enable Timer0 interrupt */ 
    ENABLE_GLOBAL_INTERRUPT; 
		set_IE_ES;                                  /* Enable UART0 interrupt */
    set_IE_EA;
		
		
		while(1){
			
    if (receiveFlag)
    {
      receiveFlag = 0;
      clr_IE_ES;
      UART_Send_Data(UART0,receive[i]);
			i++;
      set_IE_ES;
	   } 


		if(LedFlag == 11){
			flag = receive[6];
			if(flag == 0xFF){
					P12 = 0;
					LedFlag = 0;
					j = 0;
				//	UART_Send_Data(UART0,"chang guan");
			}
			else if(flag == 0x00){
					P12 = 1;
					LedFlag = 0;
					j = 0;
					//UART_Send_Data(UART0,"chang kai");
			}
			else if(0x00< flag < 0x0B){
					T = flag - '0' ;
				//	T = T + 0;
					P12 = 0;
					UART_Send_Data(UART0,flag);
					for(i =0;i < T;i++){
						Timer0_Delay(24000000,100,9998);
					}
					P12 = 1;
					LedFlag = 0; 
					j =0;
					UART_Send_Data(UART0,flag);
			}
		}
	}		
}
