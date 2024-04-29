#pragma once

const IPAddress MQTT_HOST(192, 168, 1, 150);
const int MQTT_PORT = 1883;

AsyncMqttClient mqttClient;

String GetPayloadContent(char* data, size_t len)
{
	String content = "";
	for(size_t i = 0; i < len; i++)
	{
		content.concat(data[i]);
	}
	return content;
}

void SuscribeMqtt()
{
	uint16_t packetIdSub = mqttClient.subscribe("device/0/#", 0);
	Serial.print("Subscribing at QoS 2, packetId: ");
	Serial.println(packetIdSub);
}

void updateGPIO(String input, bool value)
{
	String payload;
	StaticJsonDocument<300> doc;
	doc["command"] = "updateGPIO";
	doc["id"] = input;
	doc["status"] = value;
	serializeJson(doc, payload);

	mqttClient.publish("device/0/GPIO", 0, true, (char*)payload.c_str());

	Serial.print(input);
	Serial.println(value ? String(" ON") : String(" OFF"));
}

void OnMqttReceived(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
	Serial.print("Received on ");
	Serial.print(topic);
	Serial.print(": ");

	String content = GetPayloadContent(payload, len);

	StaticJsonDocument<200> doc;
	DeserializationError error = deserializeJson(doc, content);
	if(error) return;

	int id = doc["id"];
	bool ledStatus = doc["status"];

	String command = doc["command"];
	if(content.indexOf("GPIO") > 0 && command == "setGPIO")
		setGPIO(doc["id"], (bool)doc["status"]);
	else if(content.indexOf("PWM") > 0 && command == "setPWM")
		setPWM(doc["id"], (int)doc["pwm"]);
	else if(content.indexOf("Action") > 0 && command == "doAction")
		doAction(doc["id"]);
	else
	{
		//otras acciones
	}

}
