> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/como-controlar-un-esp8266-con-websocket-y-json/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## como-controlar-un-esp8266-con-websocket-y-json
```cpp
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "API.hpp"
#include "WebSockets.hpp"
#include "Server.hpp"
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_AWS.hpp"

void setup(void)
{
  Serial.begin(115200);
  SPIFFS.begin();
  
  ConnectWiFi_STA();

  InitServer();
  InitWebSockets();
}

void loop(void)
{
}
```

```cpp
AsyncWebServer server(80);

void InitServer()
{
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(400, "text/plain", "Not found");
  });

  server.begin();
  Serial.println("HTTP server started");
}
```

```cpp
void setData(AsyncWebSocketClient * client, String request)
{
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  if (error) { return; }

  int id = doc["id"];
  bool ledStatus = doc["status"];
  Serial.println(id);
  Serial.println(ledStatus);
}

void getData(AsyncWebSocketClient * client, String request)
{
   String response;
   StaticJsonDocument<300> jsonDoc;
   jsonDoc["id"] = random(0,10);
   jsonDoc["status"] = random(0,2);
   serializeJson(jsonDoc, response);
   
   client->text(response);
}
```

```cpp
AsyncWebSocket ws("/ws");

void ProcessRequest(AsyncWebSocketClient * client, String request)
{
  Serial.println(request);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  if (error) { return; }
  
  String command = doc["command"];
  if(command == "Set")
  {
    setData(client, request);
  }
  if(command == "Get")
  {
    getData(client, request);
  }
}
```

```html
<!DOCTYPE html>
<html class="no-js" lang="">
   <head>
      <meta charset="utf-8">
      <meta http-equiv="x-ua-compatible" content="ie=edge">
      <title>ESP8266 Json Websocket</title>
      <meta name="description" content="">
      <meta name="viewport" content="width=device-width, initial-scale=1">
   </head>
 
   <body>
     <div>
      Radio:<br>
      <input type="text" id="ledNumber" name="ledNumber" value="10" checked><br>
      <input type="radio" id="ledOn" name="status" value="true" checked>
      <label for="ledOn">ON</label><br>
      <input type="radio" id="ledOff" name="status" value="false">
      <label for="ledOff">OFF</label><br>
      <button type="button" onclick="sendData()">Send data</button>
    </div>
    <div>
      <br>
      <button type="button" onclick="getData()">Get Data!</button>
      <label id="receivedText"/>
    </div>
  </body>
  
    <script type="text/javascript" src="./js/main.js"></script>
</html>
```

```js
var connection = new WebSocket('ws://' + location.hostname + '/ws', ['arduino']);

connection.onopen = function () {
  console.log('Connected: ');
};

connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};

connection.onmessage = function (e) {
  console.log('Server: ', e.data);
  processData(e.data);
};

connection.onclose = function () {
  console.log('WebSocket connection closed');
};

function sendData()
{
  let ledNumber = document.getElementById('ledNumber');
  let ledStatus = document.querySelector('input[name="status"]:checked');
 
  let data = {
    command : "Set",
    id: ledNumber.value,
    status: ledStatus.value
  }
  let json = JSON.stringify(data);

  connection.send(json);
}

function getData()
{
  let data = {
    command : "Get"
  }
  let json = JSON.stringify(data);

  connection.send(json);
}

function processData(data)
{
  let json = JSON.parse(data); 
  console.log(json);
  let receivedMsg = 'Received: GPIO ' + json.id + ' ' + (json.status == 1 ? "ON" : "OFF");
  document.getElementById('receivedText').textContent = receivedMsg;
}
```


