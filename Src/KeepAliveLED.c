/*
 * KeepAliveLED.c
 *
 *  Created on: Sep 6, 2018
 *      Author: marlon
 */

#include "KeepAliveLED.h"
#include "main.h"
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"

void blinkLed(void *pvParameters)
{
	TickType_t xDelay = 500 / portTICK_PERIOD_MS;
	for(;;)
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		vTaskDelay(xDelay);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		vTaskDelay(xDelay);
	}
}
