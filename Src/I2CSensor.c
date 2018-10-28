/*
 * Temperatuurlezing.c
 *
 *  Created on: 12 sep. 2018
 *      Author: Thijs
 */

#include <I2CSensor.h>
#include <cmsis_os.h>

static I2C_HandleTypeDef *hi2c1;

void I2CSensorInit(I2C_HandleTypeDef *HandlePointer)
{
	hi2c1 = HandlePointer;
}

int16_t I2CGetTemperature()
{
	uint8_t buffer[2];
	int16_t rawT;

	buffer[0]=0xE3;									        //Trigger Temperature measurement  0xE3
	HAL_I2C_Master_Transmit(hi2c1,0x40<<1,buffer,1,100);  	//Device address 0x40 in the datasheet is shifted 1-bit to the left.
	//vTaskDelay(20);									//2 bytes are transmitting to the slave: buffer[0] and buffer[1]
	HAL_I2C_Master_Receive(hi2c1,0x40<<1,buffer,2,100);	    //Receive 2 bytes, store into buffer[0] and buffer[1]
	rawT = buffer[0]<<8 | buffer[1]; 							//Combine 2 8-bit into 1 16bit, buffer[0] : MSB data and buffer[1] : LSB data
	return ((rawT*176)/65536)-46;					//Raw sensor numbers converted to temperature
}

uint16_t I2CGetHumidity()
{
	uint8_t buffer[2];
	uint16_t rawH;

	buffer[0]=0xE5;		    								//Trigger Humidity measurement  0xE5
	HAL_I2C_Master_Transmit(hi2c1,0x40<<1,buffer,1,100);
	//vTaskDelay(20);
	HAL_I2C_Master_Receive(hi2c1,0x40<<1,buffer,2,100);
	rawH = buffer[0]<<8 | buffer[1]; 							//Combine 2 8-bit into 1 16bit again
	return ((rawH*125)/65536)-6;							//Raw sensor numbers converted to humidity
}

uint32_t I2CGetPressure(){
	uint8_t buffer[3];
	uint32_t Pressure;


	buffer[0] = 0x00;
	HAL_I2C_Mem_Write(hi2c1, 0x60<<1, 0x26, I2C_MEMADD_SIZE_8BIT, buffer, 1, 100);
	vTaskDelay(20);

	buffer[0] = 0x07;
	HAL_I2C_Mem_Write(hi2c1, 0x60<<1, 0x13, I2C_MEMADD_SIZE_8BIT, buffer, 1, 100);
	vTaskDelay(20);

	buffer[0] = 0x02;
	HAL_I2C_Mem_Write(hi2c1, 0x60<<1, 0x26, I2C_MEMADD_SIZE_8BIT, buffer, 1, 100);
	vTaskDelay(100);

	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	HAL_I2C_Mem_Read(hi2c1, 0x60<<1, 0x00, I2C_MEMADD_SIZE_8BIT, buffer, 1, 100);
	vTaskDelay(100);

	HAL_I2C_Mem_Read(hi2c1, 0x60<<1, 0x01, I2C_MEMADD_SIZE_8BIT, &buffer[0], 1, 100);
	vTaskDelay(100);

	HAL_I2C_Mem_Read(hi2c1, 0x60<<1, 0x02, I2C_MEMADD_SIZE_8BIT, &buffer[1], 1, 100);
	vTaskDelay(100);

	HAL_I2C_Mem_Read(hi2c1, 0x60<<1, 0x03, I2C_MEMADD_SIZE_8BIT, &buffer[2], 1, 100);


	Pressure = (buffer[0] << 16 | buffer[1] << 8 | buffer[2]);
	Pressure >>=6;

	return Pressure;
}
