#include "MS51.H"
bit LedFlag;


void main (void)
{
		int i = 0;
		int s;
    P12_PUSHPULL_MODE;

    ENABLE_TIMER1_MODE0;                           /* Timer 0 mode configuration */
    MODIFY_HIRC_24();
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;

    ENABLE_TIMER0_INTERRUPT;                       /* enable Timer0 interrupt */ 
    ENABLE_GLOBAL_INTERRUPT; 

		P12 = 0;
			for(i =0;i < 5;i++){
					Timer0_Delay(24000000,5900,1000);
				}

			P12 = 1;
		}