/*
 * WifiServer.c
 *
 *  Created on: Sep 13, 2018
 *      Author: marlon
 */

#include "WifiServer.h"
#include "ESP8266AT.h"
#include "cmsis_os.h"

#define SSID "Weather"
#define PASSWORD "password"

void wifiAPMode(void *pvParameters)
{
	int temperature = 25;
	int humidity = 55;
	wifiInit((UART_HandleTypeDef *) pvParameters);
	wifiReset();
	vTaskDelay(1000);
	wifiMux(WIFI_muxEnabled);
	vTaskDelay(10);
	wifiSetMode(WIFI_softAP);
	vTaskDelay(10);
	wifiConfigAP(SSID,PASSWORD,3,WIFI_encWPA2_PSK);
	vTaskDelay(10);
	wifiStartServer(54000);
	vTaskDelay(10);
	for(;;)
	{
		wifiSend("{\"temperature\": 20, \"humidity\": 55}\n");
		vTaskDelay(3000);
		wifiSend("{\"temperature\": 23, \"humidity\": 51}\n");
		vTaskDelay(3000);
		wifiSend("{\"temperature\": -1, \"humidity\": 57}\n");
		vTaskDelay(3000);
	}
}
