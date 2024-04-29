#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "Server.hpp"
#include "ESP32_Utils.hpp"

const int LED_PIN = 0; // Sustituir con datos de vuestra placa

void setup(void)
{
	pinMode(LED_PIN, OUTPUT);
	Serial.begin(115200);
	SPIFFS.begin();
	
	ConnectWiFi_STA();

	InitServer();
}

void loop(void)
{
}
