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
	uint16_t packetIdSub = mqttClient.subscribe("hello/world", 0);
	Serial.print("Subscribing at QoS 2, packetId: ");
	Serial.println(packetIdSub);
}

void PublishMqtt()
{
	String payload = "";

	// obtendriamos datos de GPIO, estado...
	StaticJsonDocument<300> jsonDoc;
	jsonDoc["id"] = random(0, 10);
	jsonDoc["status"] = random(0, 2);
	serializeJson(jsonDoc, payload);

	mqttClient.publish("hello/world", 0, true, (char*)payload.c_str());
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

	Serial.print(" Id:");
	Serial.print(id);
	Serial.print(" Status:");
	Serial.println(ledStatus);
}
