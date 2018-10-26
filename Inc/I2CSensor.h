#ifndef I2CSENSOR_H_
#define I2CSENSOR_H_

#include "stm32f0xx_hal.h"

void I2CSensorInit(I2C_HandleTypeDef *);
int I2CGetTemperature();
int I2CGetHumidity();
int I2CGetPressure();

#endif /* I2CSENSOR_H_ */
