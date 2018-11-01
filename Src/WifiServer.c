/*
 * WifiServer.c
 *
 *  Created on: Sep 13, 2018
 *      Author: marlon
 */

#include "WifiServer.h"

#include <string.h>
#include "cmsis_os.h"

#include "ESP8266AT.h"
#include "I2CSensor.h"
/*
 * Configurable options begin here
 * | | | | | | | | | | | | |
 * V V V V V V V V V V V V V
 */

#define APSSID "WeaFer Station"
#define APPASSWORD "password"
#define APPORT 54000

#define STASSID "WeaFer Router"
#define STAPASSWORD "weaferstation"
#define STASERVERIP "94.214.78.158"
#define STASERVERPORT 80

#define APIKEY "32c7df502dada0c2a14d48c7288d06ba" //Emoncms apikey
#define NODENAME "WeaFer" //Name displayed in emoncms

#define httpRequestPost "POST /emoncms/input/post HTTP/1.1"
#define httpRequestHost "Host: emoncms.kutsite.org"
#define httpRequestConnection "Connection: close"
#define httpRequestLength "Content-Length: "
#define httpRequestType "Content-Type: application/x-www-form-urlencoded"

/*
 * ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
 * | | | | | | | | | | | | |
 * End of options
 */

static char bufferHttpRequest[300];
static char bufferHttpData[200];
static char jsonBuffer[200];

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
	int16_t temperature;
	uint16_t humidity;
	uint32_t pressure;
	temperature = I2CGetTemperature();
	humidity = I2CGetHumidity();
	pressure = I2CGetPressure();
	sprintf(jsonBuffer,"{ \"temperature\":%d, \"humidity\":%d, \"pressure\":%ld }",
			temperature,
			humidity,
			pressure);
	return jsonBuffer;

}

/*
 * AP task.
 * Accepts a connection from the qtApp.
 */
void wifiAPMode(void *pvParameters) //pvParameters[0] == &HUART2 pvParameters[1] == &I2C
{
	char *jsonStr;
	UART_HandleTypeDef *uart;
	I2C_HandleTypeDef *i2c;

	uart = ( (UART_HandleTypeDef **) pvParameters )[0];
	i2c = ( (I2C_HandleTypeDef **) pvParameters )[1];

	I2CSensorInit(i2c);
	wifiInit(uart);

	wifiReset();
	vTaskDelay(5000);

	wifiMux(WIFI_muxEnabled);
	vTaskDelay(10);

	wifiSetMode(WIFI_softAP);
	vTaskDelay(10);

	wifiConfigAP(APSSID,APPASSWORD,3,WIFI_encWPA2_PSK);
	vTaskDelay(10);

	wifiStartServer(APPORT);
	vTaskDelay(10);

	for(;;)
	{
		jsonStr = readSensorsJson();

		wifiSendStr(0,jsonStr); //Keep sending data to link 0
		vTaskDelay(3000);
	}
}
/*
 * Hybrid task.
 * Sends data to emoncms server and accepts a connection from the qtApp.
 */
void wifiHybridMode(void *pvParameters)
{
	char *jsonStr;
	UART_HandleTypeDef *uart;
	I2C_HandleTypeDef *i2c;

	uart = ( (UART_HandleTypeDef **) pvParameters )[0];
	i2c = ( (I2C_HandleTypeDef **) pvParameters )[1];

	I2CSensorInit(i2c);
	wifiInit(uart);

	wifiReset();
	vTaskDelay(5000);

	wifiMux(WIFI_muxEnabled);
	vTaskDelay(10);

	wifiSetMode(WIFI_hybrid);
	vTaskDelay(10);

	wifiConfigAP(APSSID,APPASSWORD,3,WIFI_encWPA2_PSK);
	vTaskDelay(10);

	wifiConfigStation(STASSID,STAPASSWORD);
	vTaskDelay(10000);

	wifiStartServer(APPORT);
	vTaskDelay(100);

	for(;;)
	{
		wifiConnect(3,STASERVERIP,STASERVERPORT); //Connect link1 to the http server
		jsonStr = readSensorsJson();

		wifiSendStr(0,jsonStr); //Keep sending data to link 0
		vTaskDelay(1000);
		wifiSendStr(3,createHttpRequest(jsonStr)); //Send a http request with the jsonstring to the http server.

		vTaskDelay(2000);
	}
}
