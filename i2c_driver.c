/****************************************************************************************************************
* @file: i2c_driver.c
* @brief: This is driver file for I2C Controller.
*
* @uthor:amar.shinde
* @created:02/05/2023.
*****************************************************************************************************************/
#include"i2c_driver.h"

void i2c_init( uint32_t BitRate )
{
		uint32_t clk_div = 0;
		PINSEL0 = (PINSEL0 & ~(0xF << 4)) | /* clear the previous PINSEL settings */
							(I2C0SCL | I2C0SDA);			/* select the P0.2 as ACL & P0.3 as SDA */
		clk_div = (PCLK / BitRate);					/* Clock divider for desired BitRate @ PCLK */
		I2SCLL  = (clk_div / 2);						/* CLock High for 50% Duty Cycle */
		I2SCLH  = (clk_div / 2);						/* CLock Low  for 50% Duty Cycle */
		I2CONSET |= I2EN; 									/* Enable The I2C Interface */
}

void i2c_byte_write( uint8_t sa, uint8_t mem, uint8_t data )
{
		I2CONSET = I2STA;			/* generate start condition */
		while( SI == 0 );		/* wait till I2C Flag Not Assert */
		if( I2STAT != START_COND ) {	/* check for start condition is generated OR Not */
			I2CONCLR = I2SIC;						/* else clear flag and return */
			return;
		}
		I2DAT = sa;					/* load slave address to broadcast over I2C Bus */
		I2CONCLR = I2SIC;		/* clear the Start condition Flag */
		while( SI == 0 );		/* wait till I2C Flag Not Assert for SA + R/w */
		if( I2STAT != ACK_SA_W ) { /* if SA is not recognized by any slave then stop comm. */
				I2CONCLR = I2SIC | I2STO;
				return;
		}
		
		I2DAT = mem;				/* load memory address to select desired location in slave */
		I2CONCLR = I2SIC;		/* clear the I2C SI Flag */
		while( SI == 0 );		/* wait till SI FLag Not Assert */
		if( I2STAT != ACK_DAT_W )	{ /* if NACK on invalid memory address then STOP, else Go Ahead  */
				I2CONCLR = I2SIC | I2STO;
				return;
		}
			
		I2DAT = data;				/* now load data to send to memory address in Slave device */
		I2CONCLR = I2SIC;		/* clear the I2C SI Flag */
		while( SI == 0 );		/* wait till SI FLag Not Assert */
		if( I2STAT != ACK_DAT_W ) {	/* if NACK on data NOT written from slave then STOP Or Repeated Start */
				I2CONCLR = I2SIC | I2STO;
				return;
		}
		/* clear SI Flag and generate STOP Condition */
		I2CONCLR = I2SIC | I2STO;
		return;
}

uint8_t i2c_byte_read( uint8_t sa, uint8_t mem ) 
{
		I2CONSET = I2STA;			/* generate start condition */
		while( SI == 0);			/* wait till I2C Flag Not Assertt */
		if( I2STAT != START_COND ) {/* check for start condition is generated OR Not */
				I2CONCLR = I2SIC | I2STO;/* else clear flag and return */
				return 0;
		}
		
		I2DAT = sa;					/* load slave address to broadcast over I2C Bus */
		I2CONCLR = I2SIC;		/* clear the I2C SI Flag */
		while( SI == 0 );		/* wait till SI FLag Not Assert */
		if( I2STAT != ACK_SA_W ) { /* if SA is not recognized by any slave then stop comm. */
				I2CONCLR = I2SIC | I2STO;
				return 0;
		}
		
		I2DAT = mem;				/* load memory address to select desired location in slave */
		I2CONCLR = I2SIC;		/* clear the I2C SI Flag */
		while( SI == 0 );		/* wait till SI FLag Not Assert */
		if( I2STAT != ACK_DAT_W ){/* if NACK on invalid memory address then STOP, else Go Ahead  */
				I2CONCLR = I2SIC | I2STO;
				return 0;
		}
	
		I2CONCLR = I2SIC;		/* clear the I2C SI Flag */
		I2CONSET = I2STA;		/* Generate Repeated START Condition */
		while( SI == 0 );		/* wait till SI FLag Not Assert */
		if( I2STAT != REP_START ) { /* if Repeated Start Condition is not generated, STOP Comm & return  */
				I2CONCLR = I2SIC | I2STO;
				return 0;
		}
	
		I2DAT = (sa | RD);		/* load the Slave Address with Read mode */
		I2CONCLR = I2SIC;			/* clear the i2C SI FLag */
		while( SI == 0 );			/* wait till SI Flag Not Assert */
		if( I2STAT != ACK_SA_R ) {
				I2CONCLR = (I2SIC | I2STO);
				return 0;
		}
		
		I2CONCLR = I2SIC;		/* clear the SI FLag */
		while( SI == 0 );		/* wait till data is received in I2DAT Reg & to SI FLag Assert */
		I2CONCLR = (I2SIC | I2STO);	/* return NACK and generate Stop Condition */
		return I2DAT;				/* return the data (received) avaiable in I2DAT */
}


