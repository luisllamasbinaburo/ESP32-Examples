#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncMqttClient.h>
#include <ArduinoJson.h>

#include "config.h" // Sustituir con datos de vuestra red
#include "API.hpp"
#include "MQTT.hpp"
#include "Server.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_MQTT_Async.hpp"
#include "ReactiveArduinoLib.h"

auto obsD0 = Reactive::FromDigitalInput(0);
auto obsD5 = Reactive::FromDigitalInput(5);
auto obsD6 = Reactive::FromDigitalInput(6);
auto obsD7 = Reactive::FromDigitalInput(7);

void setup(void)
{
	Serial.begin(115200);
	SPIFFS.begin();

	delay(500);

	WiFi.onEvent(WiFiEvent);
	InitMqtt();

	ConnectWiFi_STA();
	InitServer();

	obsD0.Distinct().Do([](int i) { updateGPIO("D0", i); });
	obsD5.Distinct().Do([](int i) { updateGPIO("D5", i); });
	obsD6.Distinct().Do([](int i) { updateGPIO("D6", i); });
	obsD7.Distinct().Do([](int i) { updateGPIO("D7", i); });
}

void loop()
{
	obsD0.Next();
	obsD5.Next();
	obsD6.Next();
	obsD7.Next();
}
