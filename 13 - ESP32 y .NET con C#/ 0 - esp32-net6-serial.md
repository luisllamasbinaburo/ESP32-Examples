> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-net6-serial/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## Código ESP32
```cpp
void Update()
{
  if(isOn == false &amp;&amp; GetIsTumbado() == false)
  {
    isOn = true;
    Serial.println("A");
  }
  else if(isOn == true &amp;&amp; GetIsTumbado() == true)
  {
    isOn = false;
    Serial.println("B");
  }
}
```

```cpp
void Update()
{
  if (Serial.available())
  {
    auto content = Serial.readStringUntil(‘\n’);
    if(content == "A") isOn = true;
    if(content == "B") isOn = false;

    Render();
  }
}
```



## Código NET6
```csharp
ArduinoPort arduinoPort = new ArduinoPort();
arduinoPort.DataArrived += ArduinoPort_DataArrived;

// ejemplo USB port en Windows
arduinoPort.Open("COM4", 115200);

// ejemplo USB port en Linux
//arduinoPort.Open("/dev/ttyUSB0", 115200);

Console.ReadLine();

void ArduinoPort_DataArrived(object? sender, EventArgs? e)
{
  var lastRecieved = arduinoPort.LastRecieved;
  Console.WriteLine(lastRecieved);
}
```

```csharp
var isOn = false;
var timer = Observable.Interval(TimeSpan.FromSeconds(2))
  .Subscribe(async _ =>
  {
    var message = isOn ? "A" : "B";
    isOn = !isOn;
    
    arduinoPort.Write(message);
    Console.WriteLine(message);
  });
```


