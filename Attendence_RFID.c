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

/* global data */
uint8_t i;
char stdid[15];

/**********************************
* Hard-coded Id's in Database
***********************************
*	Id_001: vectind@b001
* Id_002: vectind@b002
* Id_003: vectind@b003
* ...
* Id_999: vectind@b999
***********************************/

uint32_t MarkAttendence(char* stdid);
char* MatchInstitute(char* iid, char* sid);

int main()
{
		uint32_t rollno;
	
		uart0_init( 9600 );
		config_vic( INTR_UART0, Uart0_IRQ_Handler, SLOT0 );
		config_uart_interrupt( UART0 );
		Irq_Intr_Enable( INTR_UART0 );
		
		while(1)
		{
				if( i == 12 )
				{	
						stdid[i] = '\0';
						if( (rollno = MarkAttendence(stdid)) ) {
								uart0_tx_string("vectind@b");
								uart0_integer(rollno);
								uart0_tx_string("\n\r");
						}
						else {
							uart0_tx_string("Invalid Id\n\r");
						}
						i = 0;
				}
		}
}

uint32_t MarkAttendence( char * stdid )
{
		char * p;
		uint32_t sid = 0, i = 0;
		p = MatchInstitute( "vectind@b", stdid  );
		if( p != 0 )
		{
				while( p[i] != '\0' )
				{
						sid = ((sid * 10) + ( p[i] - 48 ));
						i++;
				}
				if( sid <= 999 )
				{
					//update the roll no
					return sid;
				}
		}
		return 0;
}

char * MatchInstitute( char * iid, char * sid )
{
			int i = 0;
			while( iid[i] != '\0' )
			{
					if( iid[i] != sid[i] )
						return 0;
					i++;
			}
			return &sid[i];
}
