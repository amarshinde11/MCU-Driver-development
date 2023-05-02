/********************************************************************************************************************************
* @file: main.c 
* @brief: This is main file contains the i2c_init() fun call to initialize the i2c controller, also contains function calls to 
*					configure i2c interrupt, uart_init, and data processing fun calls, etc.
*	
* @uthor: amar.shinde
* @created: 01/05/2023.
*********************************************************************************************************************************/
#include"i2c_driver.h"
#include"ctypes.h"

int main()
{
		uint8_t data;
		i2c_init( I2C_100Kbps );
		while(1)
		{
			i2c_byte_write( 0xA0, 0x05, 'A' );
		}
}
