#ifndef I2CSENSOR_H_
#define I2CSENSOR_H_

#include "stm32f0xx_hal.h"

void TemperatuurInit();
int Temperatuur();
int Luchtvochtigheid();

#endif /* I2CSENSOR_H_ */
