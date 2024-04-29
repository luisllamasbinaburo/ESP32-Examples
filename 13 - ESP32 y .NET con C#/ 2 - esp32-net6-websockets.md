> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-net6-websockets/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## Código ESP32
```cpp
void InitWebSockets()
{
    webSocket.begin(ApiHost, 81, "/API");
    webSocket.onEvent(webSocketEvent);
    Serial.println("Connected websockets");
}

void SendA()
{
webSocket.sendTXT("A");
}

void SendB()
{
    webSocket.sendTXT("B");
}
```

```cpp
void setup()
 {
    Serial.begin(115200);

    WIFI_Connect();

    delay(2000);
    InitWebSockets();
}

bool isOn = false;
void Update()
{
    if (M5.BtnA.wasPressed())
    {
        if (isOn == false)
        {
            isOn = true;
            Serial.println("A");
            SendA();
        }
        else if (isOn == true)
        {
            isOn = false;
            Serial.println("B");
            SendB();
        }
    }
}

void loop()
{
    M5.update();
    webSocket.loop();
    delay(10);

    Update();
}
```



## Código NET6
```csharp
public class ArduinoWebsocket : WebSocketBehavior
{
public static string LastRecieved { get; private set; } = "";

    public static event EventHandler DataArrived;

    protected override void OnMessage(MessageEventArgs e)
    {
        LastRecieved = e.Data;
        DataArrived?.Invoke(this, new EventArgs());
    }
}
```

```csharp
InitWebSocketServer();

Console.ReadLine();

void InitWebSocketServer()
{
    var web = new WebSocketServer(81);
    web.AddWebSocketService<ArduinoWebsocket>("/API");

    ArduinoWebsocket.DataArrived += DataArrived;
    web.Start();
}

void DataArrived(object sender, EventArgs e)
{
    if (ArduinoWebsocket.LastRecieved == "A")
    {
        Console.WriteLine("A");
    }
    else if (ArduinoWebsocket.LastRecieved == "B")
    {
        Console.WriteLine("B");
    }
}
```


