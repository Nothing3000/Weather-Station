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

#define APSSID "WeaFer Station"
#define APPASSWORD "password"

#define STASSID "WeaFer Router"
#define STAPASSWORD "weaferstation"

#define SERVERIP "94.214.78.158"

#define APIKEY "32c7df502dada0c2a14d48c7288d06ba"
#define NODENAME "WeaFer"

#define httpRequestPost "POST /emoncms/input/post HTTP/1.1"
#define httpRequestHost "Host: emoncms.kutsite.org"
#define httpRequestConnection "Connection: close"
#define httpRequestLength "Content-Length: "
#define httpRequestType "Content-Type: application/x-www-form-urlencoded"

static char bufferHttpRequest[300];
static char bufferHttpData[200];

static char *createHttpRequest(char *jsonStr)
{
	sprintf(bufferHttpData,"node=%s&fulljson=%s&apikey=%s",
			NODENAME,
			jsonStr,
			APIKEY
			);
	sprintf(bufferHttpRequest,"%s\n%s\n%s\n%s%d\n%s\n\n%s",
			httpRequestPost,
			httpRequestHost,
			httpRequestConnection,
			httpRequestLength,
			strlen(bufferHttpData),
			httpRequestType,
			bufferHttpData
			);
	return bufferHttpRequest;
}

static char *readSensorsJson()
{
	int temperature,humidity,pressure;
	char *jsonStr;
	jsonStr = pvPortMalloc(200*sizeof(char));
	temperature = I2CGetTemperature();
	humidity = I2CGetHumidity();
	pressure = I2CGetPressure();
	sprintf(jsonStr,"{ \"Temperature\":%d, \"Humidity\":%d, \"Pressure\":%d }",
			temperature,
			humidity,
			pressure);
	return jsonStr;

}

void wifiAPMode(void *pvParameters) //pvParameters[0] == &HUART2 pvParameters[1] == &I2C
{
	char *jsonStr;
	UART_HandleTypeDef *uart;
	I2C_HandleTypeDef *i2c;

	uart = ((UART_HandleTypeDef **) pvParameters)[0];
	i2c = ((I2C_HandleTypeDef **) pvParameters)[1];

	I2CSensorInit(i2c);
	wifiInit(uart);
	wifiReset();
	vTaskDelay(1000);
	wifiMux(WIFI_muxEnabled);
	vTaskDelay(10);
	wifiSetMode(WIFI_softAP);
	vTaskDelay(10);
	wifiConfigAP(APSSID,APPASSWORD,3,WIFI_encWPA2_PSK);
	vTaskDelay(10);
	wifiStartServer(54000);
	vTaskDelay(10);
	for(;;)
	{
		jsonStr = readSensorsJson();

		wifiSendStr(0,jsonStr);
		vPortFree(jsonStr);
		vTaskDelay(3000);
	}
}
//{"temperature": 25, "humidity": 55}

void wifiHybridMode(void *pvParameters)
{
	char *jsonStr;
	UART_HandleTypeDef *uart;
	I2C_HandleTypeDef *i2c;

	uart = ((UART_HandleTypeDef **) pvParameters)[0];
	i2c = ((I2C_HandleTypeDef **) pvParameters)[1];

	I2CSensorInit(i2c);
	wifiInit(uart);
	wifiReset();
	vTaskDelay(5000);
	wifiMux(WIFI_muxEnabled);
	vTaskDelay(10);
	wifiSetMode(WIFI_hybrid);
	vTaskDelay(10);
	wifiConfigAP(APSSID,APPASSWORD,3,WIFI_encWPA2_PSK);
	vTaskDelay(100);
	wifiConfigStation(STASSID,STAPASSWORD);
	vTaskDelay(10000);
	wifiStartServer(54000);
	vTaskDelay(100);
	for(;;)
	{
		jsonStr = readSensorsJson();
		wifiSendStr(0,jsonStr);
		vTaskDelay(10);
		wifiConnect(1,SERVERIP,80);
		vTaskDelay(200);
		wifiSendStr(1,createHttpRequest(jsonStr));
		vPortFree(jsonStr);
		vTaskDelay(3000);
	}
}
