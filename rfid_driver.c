/***************************************************************************************************************************
* @file: uart_driver.c
* @brief: This is uart_driver source file, contains uart driver function definitions. 
*
* @uthor: amar.shinde
* @created: 29/04/2023.
****************************************************************************************************************************/
#include"uart_driver.h"

extern uint8_t i;
extern char stdid[15];

/**************************************************************************
///////////////////////////////////////////////////////////////////////////
/
/	UART0 IRQ Interrupt VIC Settings and Handler Definitions 
/
///////////////////////////////////////////////////////////////////////////
**************************************************************************/
/* UART0 IRQ Interrupt Handler */
void Uart0_IRQ_Handler(void)__irq
{
		uint8_t flag = (U0IIR & 0xFF);
		switch( flag )
		{
				case 0x2:	/* Transmit hold register empty */
								//Nothig id doing here
					break;
				case 0x4:	/* Receive data read to read */
								stdid[i++] = U0RBR;
					break;
				case 0x6: /* Error Conditions and cause of error 
										is read from U0LSR register */
					break;
				case 0xC:	/* Character Time-out indicator, i.e. No activity on RBR
											FIFO from last 3.5 to 4.5 charater time */
									//this will clear the interrupt 
					break;
		}
		VICVectAddr = 0;  /* this is very important to clear the interrupt flag 
												& update intrrupt priority */
}

void config_uart_interrupt( uint8_t uart_no )
{
	switch( uart_no )
	{
		case 0: 
					U0IER = 0x1;	//enable UART0 Rx Interrupt
			break;
		case 1:
					U1IER = 0x3;	//enable UART1 Tx & Rx Interrupt
			break;
	}
}
//////////////////////////////////////////////////////////////////////////////
/****************************************************************************/

/* UART0 init */
void uart0_init( uint32_t baud )
{
		uint32_t div_val;
		PINSEL0 &= ~0xF;
		PINSEL0 |= (TxD0|RxD0);
		U0LCR = DLAB | DATA_8BIT;
		div_val = PCLK_15MHz/(16*(baud));
		U0DLL = div_val;
		U0DLM	= (div_val >> 8);
		U0LCR &= ~DLAB;
}


/* UART0 TX and RX */
void uart0_tx( uint8_t data )
{
		U0THR = data;
		while( THRE0 == 0 );
}
uint8_t uart0_rx( void )
{
		while( RDR0 == 0 );
		return U0RBR;
}

/* UART0 RX & TX string */
void uart0_tx_string( char * str )
{
		while( *str != '\0' )
		{
				uart0_tx( *str );
				str++;
		}
}

void uart0_rx_string( char * str, uint32_t size )
{
		uint32_t i;
		for( i = 0; i < size; i++ )
		{
				str[i] = uart0_rx();
				if( str[i] == '\r' )
						break;
		}
		str[i] = '\0';
}

/* UART0 Integer / Float transmit */
void uart0_integer( int32_t int_num )
{
		char ascii_val[10];
		uint32_t i = 0, pow = 1, temp;
		if( int_num < 0 )
		{
				ascii_val[i] = '-';
				int_num = -int_num;
				i++;
		}
		temp = int_num;
		while( temp != 0 ) {
				pow = pow * 10;
				temp = temp/10;
		}
		pow = pow / 10;
		while( pow != 0 )
		{
				ascii_val[i] = (int_num / pow) + 48;
				int_num = int_num % pow;
				pow = pow / 10;
				i++;
		}
		uart0_tx_string( ascii_val );
}

void uart0_float( float f_val )
{
		uint32_t num1 = 0;
		if( f_val < 0 )
		{
				f_val = -f_val;
				num1  = f_val;
		}
		uart0_integer( num1 );
		num1 = ((f_val-num1)*100);
		uart0_integer( num1 );
}
