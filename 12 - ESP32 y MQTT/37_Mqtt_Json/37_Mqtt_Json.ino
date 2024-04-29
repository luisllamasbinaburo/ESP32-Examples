#include <WiFi.h>
#include <AsyncMqttClient.h>
#include <ArduinoJson.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "MQTT.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_MQTT_Async.hpp"

void setup(void)
{
	Serial.begin(115200);

	delay(500);

	WiFi.onEvent(WiFiEvent);
	InitMqtt();

	ConnectWiFi_STA();
}

void loop()
{
	PublishMqtt();

	delay(500);
}