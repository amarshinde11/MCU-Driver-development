/***************************************************************************************************************************
* @file: delay.c
* @brief: This is source file contains, Timer delay function definitions.
*
* @uthor: amar.shinde
* @created: 29/04/2023.
****************************************************************************************************************************/
#include"delay.h"

void delay_ms( uint32_t ms )
{
	T0TCR = 0;
	T0TC = T0PC = 0;
	T0PR = _15_KHz;
	T0TCR = 1;
	while( T0TC < ms );
	T0TCR = 0;
}

void delay_sec( uint32_t sec )
{
	T0TCR = 0;
	T0TC = T0PC = 0;
	T0PR = _15_MHz;
	T0TCR = 1;
	while( T0TC < sec );
	T0TCR = 0;
}
