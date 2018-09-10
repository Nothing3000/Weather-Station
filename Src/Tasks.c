/*
 * Tasks.c
 *
 *  Created on: Sep 10, 2018
 *      Author: marlon
 */

#include "Tasks.h"
#include "cmsis_os.h"
#include "KeepAliveLED.h"

static TaskHandle_t keepAliveLED = NULL;

void startKeepAliveLED()
{
	xTaskCreate(blinkLed,								/*Task Pointer*/
			    (const char* const) "KeepAliveLED",		/*Task Name*/
			    configMINIMAL_STACK_SIZE,				/*Stack Depth*/
			    0,										/*Parameters to pass to task*/
			    2,										/*Task Priority*/
			    &keepAliveLED);
}

void stopKeepAliveLED()
{
	if(keepAliveLED != NULL)
		vTaskDelete(keepAliveLED);
}
