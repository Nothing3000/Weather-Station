/*
 * ESP8266AT.c
 *
 *  Created on: Sep 10, 2018
 *      Author: marlon
 */

#include "ESP8266AT.h"
#include "cmsis_os.h"
#include <string.h>


wifi_t *wifiInit(UART_HandleTypeDef *huart)
{
	wifi_t *wifi;
	wifi = pvPortMalloc(sizeof(wifi_t));
	wifi -> uart = huart;
	wifi -> mode = WIFI_station;
	wifi -> dhcpmode = WIFI_dhcpDisabled;
	wifi -> muxmode = WIFI_muxDisabled;
	return wifi;
}

void wifiSetMode(wifi_t *wifi,wifimode_t mode)
{
	char data[20];
	sprintf(data,"AT+CMODE=%d\r\n",mode);
	HAL_UART_Transmit(wifi -> uart,(uint8_t *)data,strlen(data),1000);
	wifi -> mode = mode;
}

void wifiDHCP(wifi_t *wifi,wifidhcp_t dhcpmode)
{
	char data[20];
	sprintf(data,"AT+CWDHCP=%d\r\n",dhcpmode);
	HAL_UART_Transmit(wifi -> uart,(uint8_t *)data,strlen(data),1000);
	wifi -> dhcpmode = dhcpmode;
}

void wifiMux(wifi_t *wifi, wifimux_t muxmode)
{
	char data[20];
	sprintf(data,"AT+CIPMUX=%d\r\n",muxmode);
	HAL_UART_Transmit(wifi -> uart,(uint8_t *)data,strlen(data),1000);
	wifi -> muxmode = muxmode;
}

void wifiConfigAP(wifi_t *wifi,char *ssid, char *pwd, uint8_t ch, wifienc_t enc)
{
	char data[250];
	sprintf(data,"AT+CWSAP=\"%s\",\"%s\",%d,%d\r\n",ssid,pwd,ch,enc);
	HAL_UART_Transmit(wifi -> uart,(uint8_t *)data,strlen(data),1000);
}
