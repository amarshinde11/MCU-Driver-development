/***************************************************************************************************************************
* @file: delay.h
* @brief: This is header file for Timer delay.
*
* @uthor: amar.shinde
* @created: 29/04/2023.
****************************************************************************************************************************/
#ifndef _DELAY_H
#define _DELAY_H

#include<LPC21XX.H>
#include"ctypes.h"

#define _15_KHz		( 15000    )
#define _15_MHz		( 15000000 )

void delay_ms( uint32_t ms );
void delay_sec( uint32_t sec );

#endif //_DELAY_H
