/*
 * espTests.c
 *
 *  Created on: Nov 1, 2018
 *      Author: marlon
 */

#include "espTests.h"
#include "ESP8266AT.h"

#define APSSID "TestAP" //max 32
#define APSSIDMAX "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#define APPASS "password" //max 64
#define APPASSMAX "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

#define STASSID "WeaFer Router"
#define STAPASS "weaferstation"
#define FAKESTASSID "Test123321"
#define FAKESTAPASS "Test123321"

#define TESTIP "192.168.4.2"

#define STA

void testTask(void *pvParameters)
{
	wifiInit(pvParameters);
	wifiReset();

	wifiGetInfo();

	wifiSetMode(WIFI_station);
	wifiSetMode(WIFI_softAP);
	wifiSetMode(WIFI_hybrid);

	wifiMux(WIFI_muxDisabled);
	wifiMux(WIFI_muxEnabled);

	wifiDHCP(WIFI_dhcpDisabled);
	wifiDHCP(WIFI_dhcpEnabled);

	wifiConfigAP(APSSID, APPASS, 3, WIFI_encOpen);
	wifiConfigAP(APSSIDMAX, APPASSMAX, 13, WIFI_encWPA_PSK);
	wifiConfigAP(APSSID, APPASS, 13, WIFI_encWPA2_PSK);
	wifiConfigAP(APSSID, APPASS, 3, WIFI_encWPA_WPA2_PSK);

	wifiConfigStation(FAKESTASSID,FAKESTAPASS);
	wifiConfigStation(STASSID,STAPASS);

	wifiStartServer(65536);
	wifiStartServer(65535);

	wifiConnect(5,TESTIP,4445);
	wifiConnect(1,"192.168.54.90",4445);
	wifiConnect(0,TESTIP,4445);

	wifiSendStr(0,"Test");
	wifiSendStr(5,"TestTest");

	for(;;);
}
