/*
 * ESP8266AT.h
 *
 *  Created on: Sep 10, 2018
 *      Author: marlon
 */

/*
 * Wifi AT's to implement:
 * AT+CWMODE (Select WIFI mode) DONE
 * AT+CWSAP (Configure SoftAP)
 * AT+CWJAP (Connect to ap)
 * AT+CWDHCP (Set DHCP) DONE
 * AT+CIPSTA (Set ip station mode)
 * AT+CIPAP (Set ip softAP mode)
 *
 * TCP/IP AT's to implement:
 * AT+CIPSEND (Send data)
 * AT+CIPMUX (Enable multiple connections) DONE
 * AT+CIPSERVER (Configure server mode)
 *
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

typedef struct
{
	UART_HandleTypeDef *uart;
	wifimode_t	mode;
	wifidhcp_t dhcpmode;
	wifimux_t muxmode;
	char ssid[32];
	char pwd[64];
}wifi_t;

wifi_t *wifiInit(UART_HandleTypeDef *);
void wifiSetMode(wifi_t *,wifimode_t);
void wifiConnect(wifi_t *);
void wifiDHCP(wifi_t *,wifidhcp_t);
void wifiMux(wifi_t *,wifimux_t);
void wifiConfigAP(wifi_t *,char *,char *,uint8_t,wifienc_t);


#endif /* ESP8266AT_H_ */
