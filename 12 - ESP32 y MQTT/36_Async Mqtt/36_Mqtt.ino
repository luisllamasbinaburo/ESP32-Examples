#include <WiFi.h>

#include <AsyncMqttClient.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "MQTT.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_MQTT_Async.hpp"

void setup()
{
	Serial.begin(115200);

	delay(500);

	WiFi.onEvent(WiFiEvent);
	InitMqtt();

	ConnectWiFi_STA();
}

void loop()
{
	delay(1000);
	
	PublishMqtt(millis());
}