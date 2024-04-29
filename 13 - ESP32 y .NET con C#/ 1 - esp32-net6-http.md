> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-net6-http/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## Código ESP32
```cpp
#pragma once

WebServer server(80);

void handleNotFound() 
{
   server.send(404, "text/plain", "Not found");
}

void InitServer()
{
   server.on("/A", []()
   {
      server.send(200, "text/plain", "A funciona");
      Serial.println("A");
   });

   server.on("/B", []()
   {
      server.send(200, "text/plain", "B funciona");
      Serial.println("B");
   });
 
   server.onNotFound(handleNotFound);
 
   server.begin();
   Serial.println("HTTP server started");
}
```

```cpp
void setup(void) 
{
  Serial.begin(115200);

  ConnectWiFi_STA();
 
  InitServer();
}
```

```cpp
void loop()
{
  M5.update();

  server.handleClient();
  delay(100);
}
```



## Código NET6
```csharp
using System.Diagnostics;
using System.Reactive.Linq;

var isOn = false;
var timer = Observable.Interval(TimeSpan.FromSeconds(2))
.Subscribe(async _ =>
{
    isOn = !isOn;
    var url = @$"http://192.168.1.xxx/{(isOn ? "A" : "B")}";

    var response = await new HttpClient().GetAsync(url);
    var data = await response.Content.ReadAsStringAsync();
    Console.WriteLine(data);
});

Console.ReadLine();
```



## Código ESP32
```cpp
void processResponse(int httpCode, HTTPClient&amp; http)
{
  if (httpCode > 0) {
    Serial.printf("Response code: %d\t", httpCode);

    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  else {
    Serial.printf("Request failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void SendEndpointA()
{
  HTTPClient http;
  http.begin(ApiHost + "/API/EndpointA");
  int httpCode = http.GET();
  processResponse(httpCode, http);
}

void SendEndpointB()
{
  HTTPClient http;
  http.begin(ApiHost + "/API/EndpointB");
  int httpCode = http.GET();
  processResponse(httpCode, http);
}
```

```cpp
void setup() {
  Serial.begin(115200);
  WIFI_Connect();
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
      SendEndpointB();
    }
    else
    {
      isOn = false;
      Serial.println("B");
      SendEndpointA();
    }
  }
}

void loop()
{
  M5.update();

  delay(200);

  Update();
}
```



## Código NET6
```csharp
public class WebServer
{
    private readonly HttpListener _listener = new HttpListener();
    private readonly Func<httplistenerrequest, string=""> _responderMethod;

    public WebServer(Func<httplistenerrequest, string=""> method, params string[] prefixes)          
    {
        foreach (string s in prefixes) _listener.Prefixes.Add(s);

        _responderMethod = method;
        _listener.Start();
    }

    public void Run()
    {
        ThreadPool.QueueUserWorkItem((o) =>
        {
            while (_listener.IsListening)
            {
                ThreadPool.QueueUserWorkItem((c) =>
                {
                    var ctx = c as HttpListenerContext;
                        string rstr = _responderMethod(ctx.Request);
                        SendResponse(ctx, rstr);
                        ctx.Response.OutputStream.Close();
                }, _listener.GetContext());
            }   
        });
    }

    private static void SendResponse(HttpListenerContext ctx, string rstr)
    {
        ctx.Response.ContentType = "text/html";
        ctx.Response.ContentEncoding = Encoding.Unicode;

        byte[] buf = Encoding.Unicode.GetBytes(rstr);
        ctx.Response.ContentLength64 = buf.Length;
        ctx.Response.OutputStream.Write(buf, 0, buf.Length);
    }

    public void Stop()
    {
        _listener.Stop();
        _listener.Close();
    }
}
```

```csharp
InitWebServer();

Console.ReadLine();

int port;
string[] prefix;
WebServer webServer;

void InitWebServer()
{
    port = 80;
    prefix = new string[] { $"http://*/API/" };
    webServer = new WebServer(ProcessRequest, prefix);
    webServer.Run();
}

string ProcessRequest(HttpListenerRequest request)
{
    var endpoint = request.Url.LocalPath;

    if (endpoint == "/API/EndpointA")
    {
        Console.WriteLine("EndpointA");
        return "";
    }

    if (endpoint == "/API/EndpointB")
    {
        Console.WriteLine("EndpointA");
        return "";
    }

    return "Invalid address";
}
```


