#ifndef I2CSENSOR_H_
#define I2CSENSOR_H_

#include "stm32f0xx_hal.h"

void I2CSensorInit(I2C_HandleTypeDef *);
int16_t I2CGetTemperature();
uint16_t I2CGetHumidity();
uint32_t I2CGetPressure();

#endif /* I2CSENSOR_H_ */
