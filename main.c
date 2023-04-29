/***************************************************************************************
* @file: main.c
* @brief: This is main file calls uart_init() and calls to other uart driver functions  
*
* @uthor: amar.shinde
* @created: 29/04/2023.
***************************************************************************************/
#include"uart_driver.h"
#include"delay.h"
#include"config_vic.h"

uint8_t g_data0;
uint8_t g_data1;
uint8_t g_flag;

int main()
{
		uart0_init( 9600 );
		uart1_init( 9600 );

		config_vic( INTR_UART0, Uart0_IRQ_Handler, SLOT0 );
		config_vic( INTR_UART1, Uart1_IRQ_Handler, SLOT1 );

		config_uart_interrupt( UART0 );
		config_uart_interrupt( UART1 );
		
		Irq_Intr_Enable( INTR_UART0 );
		Irq_Intr_Enable( INTR_UART1 );
		
		while(1)
		{
				if( g_flag )
				{
						uart0_tx( g_data0 );
						g_flag = 0;
				}
		}
}
