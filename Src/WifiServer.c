/*
 * WifiServer.c
 *
 *  Created on: Sep 13, 2018
 *      Author: marlon
 */

#include "WifiServer.h"
#include "ESP8266AT.h"
#include "cmsis_os.h"

void wifiMain(void *pvParameters)
{
	wifiInit((UART_HandleTypeDef *) pvParameters);
	wifiReset();
	vTaskDelay(1000);
	wifiSetMode(WIFI_softAP);
	wifiConfigAP("Weather","jemoederisdik",3,WIFI_encWPA2_PSK);
	wifiMux(WIFI_muxEnabled);
	for(;;)
	{

	}
}
