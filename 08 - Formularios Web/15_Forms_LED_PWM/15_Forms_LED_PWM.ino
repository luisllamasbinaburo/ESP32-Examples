#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const int LED_PIN = 0;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

#include "config.h"  // Sustituir con datos de vuestra red
#include "Server.hpp"
#include "ESP32_Utils.hpp"

void setup(void)
{
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(LED_PIN, ledChannel);
  
	Serial.begin(115200);
	SPIFFS.begin();
	
	ConnectWiFi_STA();

	InitServer();
}

void loop(void)
{
}
