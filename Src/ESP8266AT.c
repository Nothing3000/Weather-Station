/*
 * ESP8266AT.c
 *
 *  Created on: Sep 10, 2018
 *      Author: marlon
 */

#include "ESP8266AT.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>
#include  <errno.h>
#include  <sys/unistd.h> // STDOUT_FILENO, STDERR_FILENO

#define TIMEOUT 100

static UART_HandleTypeDef * wifiUart;

static void flush()
{
	uint8_t ch[1];
	while(HAL_UART_Receive(wifiUart, ch, 1, TIMEOUT) == HAL_OK);
}

/*static int sendChar(char *data)
{
	HAL_StatusTypeDef status =
			HAL_UART_Transmit(wifiUart, (uint8_t *)data, 1, TIMEOUT);
	return (status == HAL_OK ? 1 : 0);
}

static void sendCommand(char * commandStr)
{
	for(;*commandStr; commandStr++)
	{
		while(!sendChar(commandStr));
	}
}*/

int _write(int file, char *data, int len)
{
   if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
   {
      errno = EBADF;
      return -1;
   }

   // arbitrary timeout 1000
   HAL_StatusTypeDef status =
      HAL_UART_Transmit(wifiUart, (uint8_t*)data, len, TIMEOUT);

   // return # of bytes written - as best we can tell
   return (status == HAL_OK ? len : 0);
}

int _read(int file, char *data, int len)
{
	if (file != STDIN_FILENO)
	{
		errno = EBADF;
		return 0;
	}
	HAL_StatusTypeDef status =
			HAL_UART_Receive(wifiUart, (uint8_t *)data, 1, TIMEOUT);

	return (status == HAL_OK ? 1 : 0);
}

void wifiInit(UART_HandleTypeDef *huart)
{
	wifiUart = huart;
}

void wifiSetMode(wifimode_t mode)
{
	/*char commandStr[100];
	sprintf(commandStr,"AT+CWMODE=%d\r\n",mode);
	sendCommand(commandStr);*/
	printf("AT+CWMODE=%d\r\n",mode);
}

void wifiDHCP(wifidhcp_t dhcpmode)
{
	/*char commandStr[100];
	sprintf(commandStr,"AT+CWDHCP=%d\r\n",dhcpmode);
	sendCommand(commandStr);*/
	printf("AT+CWDHCP=%d\r\n",dhcpmode);
}

void wifiMux(wifimux_t muxmode)
{
	/*char commandStr[100];
	sprintf(commandStr,"AT+CIPMUX=%d\r\n",muxmode);
	sendCommand(commandStr);*/
	printf("AT+CIPMUX=%d\r\n",muxmode);
}

void wifiConfigAP(char *ssid, char *pwd, uint8_t ch, wifienc_t enc)
{
	/*char commandStr[500];
	sprintf(commandStr,"AT+CWSAP=\"%s\",\"%s\",%d,%d\r\n",ssid,pwd,ch,enc);
	sendCommand(commandStr);*/
	printf("AT+CWSAP=\"%s\",\"%s\",%d,%d\r\n",ssid,pwd,ch,enc);
}

void wifiStartServer(int port)
{
	/*char commandStr[100];
	sprintf(commandStr, "AT+CIPSERVER=1,%d\r\n",port);
	sendCommand(commandStr);*/
	printf("AT+CIPSERVER=1,%d\r\n",port);
}

void wifiSend(const int *sensorVals)
{
	printf("AT+CIPSEND=0,%d\r\n",36);
	vTaskDelay(100);
	printf("{\"temperature\": %d, \"humidity\": %d}\n",sensorVals[0],sensorVals[1]);
}

void wifiReset()
{
	//sendCommand("AT+RST\r\n");
	printf("AT+RST\r\n");
	//printf("ATE0\r\n");
	//flush();
}
