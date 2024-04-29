#include <WiFi.h>
#include <ArduinoOTA.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_OTA.hpp"

void setup(){
	Serial.begin(115200);

	ConnectWiFi_STA();

	InitOTA();
}

void loop(){
	ArduinoOTA.handle();
}

