#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "Websockets.hpp"
#include "Server.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_AWS.hpp"

void setup(void)
{
	Serial.begin(115200);
	SPIFFS.begin();
	
	ConnectWiFi_STA();

	InitWebSockets();
	InitServer();
}

void loop(void)
{
	// Ejemplo 2, llamada desde servidor
	ws.textAll(GetMillis());
  delay(100);
}
