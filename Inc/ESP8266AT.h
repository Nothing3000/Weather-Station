/*
 * ESP8266AT.h
 *
 *  Created on: Sep 10, 2018
 *      Author: marlon
 */

#ifndef ESP8266AT_H_
#define ESP8266AT_H_

#include "stm32f0xx_hal.h"

typedef enum
{
	WIFI_station = 1,
	WIFI_softAP = 2,
	WIFI_hybrid = 3
}wifimode_t;

typedef enum
{
	WIFI_dhcpDisabled = 0,
	WIFI_dhcpEnabled = 1
}wifidhcp_t;

typedef enum
{
	WIFI_muxDisabled = 0,
	WIFI_muxEnabled = 1
}wifimux_t;

typedef enum
{
	WIFI_encOpen = 0,
	WIFI_encWPA_PSK = 2,
	WIFI_encWPA2_PSK = 3,
	WIFI_encWPA_WPA2_PSK = 4
}wifienc_t;

void wifiInit(UART_HandleTypeDef *);
void wifiSetMode(wifimode_t);
void wifiGetInfo();
void wifiConfigStation(const char *,const char *);
void wifiDHCP(wifidhcp_t);
void wifiMux(wifimux_t);
void wifiConfigAP(const char *,const char *,uint8_t,wifienc_t);
void wifiConnect(uint8_t,const char *,uint16_t);
void wifiStartServer(uint16_t);
void wifiSendStr(uint8_t,const char *);
void wifiReset();


#endif /* ESP8266AT_H_ */
