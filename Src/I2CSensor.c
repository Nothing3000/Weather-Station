/*
 * Temperatuurlezing.c
 *
 *  Created on: 12 sep. 2018
 *      Author: Thijs
 */

#include <I2CSensor.h>

static I2C_HandleTypeDef *hi2c1;

void I2CSensorInit(I2C_HandleTypeDef *HandlePointer)
{
	hi2c1 = HandlePointer;
}

int I2CGetTemperature()
{
	unsigned char buffer[2];
	unsigned int rawT;

	buffer[0]=0xE3;									        //Trigger Temperature measurement  0xE3
	HAL_I2C_Master_Transmit(hi2c1,0x40<<1,buffer,1,100);  	//Device address 0x40 in the datasheet is shifted 1-bit to the left.
	//vTaskDelay(20);											//2 bytes are transmitting to the slave: buffer[0] and buffer[1]
	HAL_I2C_Master_Receive(hi2c1,0x40<<1,buffer,2,100);	    //Receive 2 bytes, store into buffer[0] and buffer[1]
	rawT = buffer[0]<<8 | buffer[1]; 							//Combine 2 8-bit into 1 16bit, buffer[0] : MSB data and buffer[1] : LSB data
	return ((float)rawT/65536)*175.72 -46.85;					//Raw sensor numbers converted to temperature
}

int I2CGetHumidity()
{
	unsigned char buffer[2];
	unsigned int rawH;

	buffer[0]=0xE5;		    								//Trigger Humidity measurement  0xE5
	HAL_I2C_Master_Transmit(hi2c1,0x40<<1,buffer,1,100);
	//vTaskDelay(20);
	HAL_I2C_Master_Receive(hi2c1,0x40<<1,buffer,2,100);
	rawH = buffer[0]<<8 | buffer[1]; 							//Combine 2 8-bit into 1 16bit again
	return ((float)rawH/65536)*125.0-6;							//Raw sensor numbers converted to humidity
}
