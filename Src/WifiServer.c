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
	wifi_t *wifi = wifiInit((UART_HandleTypeDef *) pvParameters);
	wifiSetMode(wifi,WIFI_hybrid);
	wifiConfigAP(wifi,"SpeklappenFi","jemoederisdik",3,WIFI_encWPA_PSK);
	for(;;)
	{

		vTaskDelay(2000);
	}
}
