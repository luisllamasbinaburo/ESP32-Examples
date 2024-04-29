> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-net6-mqtt/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## Código ESP32
```cpp
class MqttService
{
public:
  void Init()
  {
    mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
    SuscribeMqtt();

    mqttClient.setCallback([this](char* topic, uint8_t* payload, unsigned int length) -> void
    {
      this->OnMqttReceived(topic, payload, length);
    });
  }

  void ConnectMqtt()
  {
    while (!mqttClient.connected())
    {
      Serial.print("Starting MQTT connection...");
      if (mqttClient.connect(MQTT_CLIENT_NAME))
      {
        SuscribeMqtt();
      }
      else
      {
        Serial.print("Failed MQTT connection, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" try again in 5 seconds");

        delay(5000);
      }
    }
  }

  void HandleMqtt()
  {
    if (!mqttClient.connected())
    {
      ConnectMqtt();
    }
    mqttClient.loop();
  }

  void SuscribeMqtt()
  {
    mqttClient.subscribe("hello/world/net");
  }

  String payload;
  void SendB()
  {
    String topic = "hello/world/esp32";
    payload = "A";
    mqttClient.publish(topic.c_str(), payload.c_str());
  }

  void SendA()
  {
    String topic = "hello/world/esp32";
    payload = "B";
    mqttClient.publish(topic.c_str(), payload.c_str());
  }

  String content = "";
  void OnMqttReceived(char* topic, uint8_t* payload, unsigned int length)
  {
    content = "";
    for (size_t i = 0; i < length; i++)
    {
      content.concat((char)payload[i]);
    }

    Serial.println(content);
  }
};
```

```cpp
void setup() {
  Serial.begin(115200);

  WIFI_Connect();
  delay(2000);

  mqttService.Init();
}
```

```cpp
bool isOn = false;
void Update()
{
  if (M5.BtnA.wasPressed())
  {
    if (isOn == false)
    {
      isOn = true;
      Serial.println("A");
      mqttService.SendA();
    }
    else if (isOn == true)
    {
      isOn = false;
      Serial.println("B");
      mqttService.SendB();
    }
  }
}

void loop()
{
  mqttService.HandleMqtt();

  delay(10);
  Update();
}
```



## Código NET6
```csharp
internal class MqttService
{
private IMqttClient mqttClient;

    public async Task Initialize(string brokerIpAddress)
    {
        var factory = new MqttFactory();

        var options = new MqttClientOptionsBuilder()
        .WithClientId("Client1")
        .WithTcpServer(brokerIpAddress, 1883)
        .Build();

        mqttClient = factory.CreateMqttClient();

        mqttClient.ConnectedAsync += (async e =>
        {
            await mqttClient.SubscribeAsync(new MqttTopicFilterBuilder().WithTopic("hello/world/esp32").Build());
        });

        mqttClient.ApplicationMessageReceivedAsync += (async e =>
        {
            Console.WriteLine($"+ Payload = {Encoding.UTF8.GetString(e.ApplicationMessage.Payload)}");
        });

        await mqttClient.ConnectAsync(options, CancellationToken.None);
    }

    public async Task SendMqtt(object payload)
    {
        var json = JsonSerializer.Serialize(payload);

        var applicationMessage = new MqttApplicationMessageBuilder()
                                   .WithTopic("hello/world/net")
                                   .WithPayload(json)
                                   .Build();

        await Task.Run(() => mqttClient.PublishAsync(applicationMessage));

    }
}
```

```csharp
var brokerIpAddress = "192.168.1.xxx";

Console.Write(" - Initializing MQTT:");
var mqttService = new MqttService();
await mqttService.Initialize(brokerIpAddress);
Console.WriteLine(" OK");

var timer = Observable.Interval(TimeSpan.FromSeconds(2))
.Subscribe(async _ =>
{
    try
    {
        await mqttService.SendMqtt(new { data = System.DateTime.Now });
    }
    catch (Exception ex)
    {
        Console.WriteLine($"{DateTime.Now} Error sending: {ex.Message}");
    }
});

Console.ReadLine();
```


