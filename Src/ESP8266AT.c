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

static UART_HandleTypeDef * wifiUart;

int _write(int file, char *data, int len)
{
   if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
   {
      errno = EBADF;
      return -1;
   }

   // arbitrary timeout 1000
   HAL_StatusTypeDef status =
      HAL_UART_Transmit(wifiUart, (uint8_t*)data, len, 1000);

   // return # of bytes written - as best we can tell
   return (status == HAL_OK ? len : 0);
}

void wifiInit(UART_HandleTypeDef *huart)
{
	wifiUart = huart;
}

void wifiSetMode(wifimode_t mode)
{
	printf("AT+CWMODE=%d\r\n",mode);
}

void wifiDHCP(wifidhcp_t dhcpmode)
{
	printf("AT+CWDHCP=%d\r\n",dhcpmode);
}

void wifiMux(wifimux_t muxmode)
{
	printf("AT+CIPMUX=%d\r\n",muxmode);
}

void wifiConfigAP(char *ssid, char *pwd, uint8_t ch, wifienc_t enc)
{
	printf("AT+CWSAP=\"%s\",\"%s\",%d,%d\r\n",ssid,pwd,ch,enc);
}

void wifiReset()
{
	printf("AT+RST\r\n");
}
