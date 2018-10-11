/*
 * WifiServer.c
 *
 *  Created on: Sep 13, 2018
 *      Author: marlon
 */

#include "WifiServer.h"

#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"

#include "ESP8266AT.h"
#include "I2CSensor.h"

#define SSID "Weather"
#define PASSWORD "password"

void wifiAPMode(void *pvParameters) //pvParameters[0] == HUART2 pvParameters[1] == I2C
{
	int sensorVals[2] = {0,0};
	UART_HandleTypeDef *uart;
	I2C_HandleTypeDef *i2c;

	uart = (UART_HandleTypeDef *)((void **) pvParameters)[0];
	i2c = (I2C_HandleTypeDef *)((void **) pvParameters)[1];

	I2CSensorInit(i2c);
	wifiInit(uart);
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
		sensorVals[0] = I2CGetTemperature();
		sensorVals[1] = I2CGetHumidity();
		wifiSend(sensorVals);
		vTaskDelay(3000);
	}
}
//{"temperature": 25, "humidity": 55}
