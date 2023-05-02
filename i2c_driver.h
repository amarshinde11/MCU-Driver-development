/****************************************************************************************************************
* @file: i2c_driver.h
* @brief: This is header file for I2C Controller, driver function prototypes, macro-definitions, etc.
*
* @uthor:amar.shinde
* @created:02/05/2023.
*****************************************************************************************************************/
#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include<LPC21XX.h>
#include"ctypes.h"

#define PCLK					( 15000000 )

/* I2C Protocol Comm Speeds */
#define I2C_100Kbps		( 100000  )
#define I2C_500Kbps		( 500000  )
#define I2C_1Mbps			( 1000000 )
#define I2C_3_4Mbps		( 3400000 )
#define I2C_5Mbps			( 5000000 )

/* I2C Pin select */
#define I2C0SCL 			( 1 << 4 )
#define I2C0SDA				( 1 << 6 )
#define RD						( 1 )
#define WR						( 0 )

/* I2C Control Set Register */
#define I2EN					( 1 << 6 )
#define I2STA					( 1 << 5 )
#define I2STO					( 1 << 4 )
#define I2SIC					( 1 << 3 )
#define I2AA					( 1 << 2 )

/* SI flag for I2C bus actions */
#define SI				( ((I2CONSET>>3)&1) )

/* I2C Status Codes */
#define START_COND		( 0x08 )
#define REP_START			( 0x10 )

/* I2C Master Transmitter Mode Status Codes */
#define ACK_SA_W			( 0x18 )
#define NACK_SA_W			( 0x20 )
#define ACK_DAT_W			( 0x28 )
#define NACK_DAT_W		( 0x30 )

/* I2C Master Receiver Mode Status Codes */
#define ACK_SA_R			( 0x40 )
#define NACK_SA_R			( 0x48 )
#define ACK_DAT_R			( 0x50 )
#define NACK_DAT_R		( 0x58 )

extern void i2c_init( uint32_t BitRate );
extern void i2c_byte_write( uint8_t sa, uint8_t mem, uint8_t data );
extern uint8_t i2c_byte_read( uint8_t sa, uint8_t mem );

#endif //#ifndef I2C_DRIVER_H

