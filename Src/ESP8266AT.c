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
static char commandStr[200];

static void flush()
{
	uint8_t ch[1];
	while(HAL_UART_Receive(wifiUart, ch, 1, TIMEOUT) == HAL_OK);
}

/*int _write(int file, char *data, int len)
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
}turn (status == HAL_OK ? 1 : 0);
}*/

static void sendStr(const char *szText)
{
	HAL_UART_Transmit(wifiUart, (uint8_t*)szText, strlen(szText), TIMEOUT);
}

void wifiInit(UART_HandleTypeDef *huart)
{
	wifiUart = huart;
}

void wifiSetMode(wifimode_t mode)
{
	sprintf(commandStr,"AT+CWMODE=%d\r\n",mode);
	sendStr(commandStr);
	//printf("AT+CWMODE=%d\r\n",mode);
}

void wifiGetInfo()
{
	sprintf(commandStr,"AT+CIFSR\r\n");
	sendStr(commandStr);
}

void wifiConfigStation(char *ssid, char *pwd)
{
	sprintf(commandStr,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,pwd);
	sendStr(commandStr);
}

void wifiDHCP(wifidhcp_t dhcpmode)
{
	sprintf(commandStr,"AT+CWDHCP=%d\r\n",dhcpmode);
	sendStr(commandStr);
}

void wifiMux(wifimux_t muxmode)
{
	sprintf(commandStr,"AT+CIPMUX=%d\r\n",muxmode);
	sendStr(commandStr);
}

void wifiConfigAP(char *ssid, char *pwd, uint8_t ch, wifienc_t enc)
{
	sprintf(commandStr,"AT+CWSAP=\"%s\",\"%s\",%d,%d\r\n",ssid,pwd,ch,enc);
	sendStr(commandStr);
}

void wifiConnect(uint8_t id,char *ip,uint16_t port)
{
	sprintf(commandStr,"AT+CIPSTART=%d,\"TCP\",\"%s\",%d\r\n",id,ip,port);
	sendStr(commandStr);
}

void wifiStartServer(uint16_t port)
{
	sprintf(commandStr, "AT+CIPSERVER=1,%d\r\n",port);
	sendStr(commandStr);

}

void wifiSendStr(uint8_t id,const char *szText)
{
	sprintf(commandStr,"AT+CIPSEND=%d,%d\r\n",id,strlen(szText)+1);
	sendStr(commandStr);
	vTaskDelay(50);
	sendStr(szText);
	sendStr("\n");

}

void wifiReset()
{
	flush();
	sendStr("\r\n\r\n");
	sendStr("AT+RST\r\n");
}
