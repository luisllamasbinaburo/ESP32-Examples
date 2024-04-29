#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncMqttClient.h>
#include <ArduinoJson.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "Server.hpp"
#include "MQTT.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_MQTT_Async.hpp"

void setup(void)
{
	Serial.begin(115200);
	SPIFFS.begin();

	delay(500);

	WiFi.onEvent(WiFiEvent);
	InitMqtt();

	ConnectWiFi_STA();
	InitServer();
}

void loop()
{
	PublishMqtt();

	delay(1000);
}