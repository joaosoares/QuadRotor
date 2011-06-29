/*	This module holds all initialization and writing/reading functions for	**
**	the intertial sensors: Accelerometer and Gyroscope. Requires i2c Module **
**	By Paulo Carvalho V2.00													*/

#include "i2c.h"

/* Function for Writing into Sensor Registers */
void i2c_reg_write(char device, char reg, char data)
{
	/* Starts i2C interface */
	i2c_start(device + I2C_WRITE);

	/* Send Register Adress */
	i2c_write(reg);

	/* Sends Desired Register Value */
	i2c_write(data);
}

/* Configures Gyro */ 
void gyro_init(void)
{	
	/* Reset IMU */
	i2c_reg_write(GYROADRESS, PWR_MGM, (1 << H_RESET)); 
	
	/* Delay After Reset */
	_delay_us(500); 

	/* Changes Clock Source (Internal Clock) */
	i2c_reg_write(GYROADRESS, PWR_MGM, (0 << CLK_SEL));

	/* Sample Rate to 200 hz (0x07 = 200 hz) */
	i2c_reg_write(GYROADRESS, SMPLRT_DIV, 0x04);

	/* Full Range + 5 hz LPF @ 1 KHZ */
	i2c_reg_write(GYROADRESS, DLPF_FS, ((3 << FS_SEL) | (6 << DLPF_CFG)));

	/* Program Interrupt and Relieve Method For Interrupt */
	i2c_reg_write(GYROADRESS, INT_CFG, ((0 << LATCH_INT_EN) | (0 << INT_ANYRD_2CLEAR) | (1 << RAW_RDY_EN)));
}

/* Reads Gyro Data and Store On External Array */
void gyro_read(int *ptr)
{
	/* Start Comunication and Send Register Adress */
	i2c_start(GYROADRESS+I2C_WRITE);
	i2c_write(GYROREGADRESS);

	/* Send Repeated Start and Read Registers*/
	i2c_rep_start(GYROADRESS+I2C_READ);

	/* Read All Axis and Add Offsets */
	ptr[3] = (i2c_readAck() << 8) |  i2c_readAck(); //Temperature
	ptr[0] = ((i2c_readAck() << 8) |  i2c_readAck()) + X_OFFSET; // X Axis
	ptr[1] = ((i2c_readAck() << 8) |  i2c_readAck()) + Y_OFFSET; // Y Axis
	ptr[2] = ((i2c_readAck() << 8) |  i2c_readNak()) + Z_OFFSET; // Z Axis

	/* Stop i2c */
	i2c_stop();
}	

/* Initializes Accelerometer */
void accel_init(void)
{
	/* Put Device Into StandBy */
	i2c_reg_write(ACCELADRESS, POWER_CTL, 0x00);
	
	/* Put Device into auto sleep */
	i2c_reg_write(ACCELADRESS, POWER_CTL, (1 << AUTO_SLEEP));
	
	/* Put Device Into Measurement Mode */
	i2c_reg_write(ACCELADRESS, POWER_CTL, (1 << MEASURE));
	
	/* Enable Interrupt */
	i2c_reg_write(ACCELADRESS, INT_ENABLE, (1 << DATA_READY));
	
	/* Select Input Source */
	i2c_reg_write(ACCELADRESS, INT_MAP, ~(1 << DATA_READY));
	
	/* Define Data Format and Range */
	i2c_reg_write(ACCELADRESS, DATA_FORMAT, ((0 << JUSTIFY) | (1 << RANGE)));
	
	/* Define Sample Rate */
	i2c_reg_write(ACCELADRESS, BW_RATE, (11 << RATE));
	
	/* Bypass Filter */
	i2c_reg_write(ACCELADRESS, FIFO_CTL, 0x00);
}			

/* Reads Data From Accelerometer */
void accel_read(int *ptr)
{
	/* Start Comunication and Send Register Adress */
	i2c_start(ACCELADRESS+I2C_WRITE);
	i2c_write(DATAX0);

	/* Send Repeated Start and Read Registers*/
	i2c_rep_start(ACCELADRESS+I2C_READ);

	/* Read All Axis */
	ptr[0] = i2c_readAck() | (i2c_readAck() << 8); // X Axis
	ptr[1] = i2c_readAck() | (i2c_readAck() << 8); // Y Axis
	ptr[2] = i2c_readAck() | (i2c_readNak() << 8); // Z Axis

	/* Stop i2c */
	i2c_stop();
}
