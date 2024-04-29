> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/comunicar-una-pagina-web-con-websockets-en-el-esp8266/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## Ejemplos de código
```cpp
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <WebSocketsServer.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "WebSockets.hpp"
#include "Server.hpp"
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_WS.hpp"

void setup(void)
{
  Serial.begin(115200);
  SPIFFS.begin();
  
  ConnectWiFi_STA();
  
  InitWebSockets();
  InitServer();
}

void loop(void)
{
  webSocket.loop();
  
  // Ejemplo 2, llamada desde servidor
  String message = GetMillis();
  webSocket.broadcastTXT(message);
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
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) 
{
  switch(type) {
  case WStype_DISCONNECTED:
    break;
  case WStype_CONNECTED:
    //IPAddress ip = webSocket.remoteIP(num);
    //webSocket.sendTXT(num, "Connected");
    break;
  case WStype_TEXT:
    String response = ProcessRequest();
    webSocket.sendTXT(num, response);
    break;
  }
}

void InitWebSockets() {
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket server started");
}
```

```cpp
String GetMillis()
{
  return String(millis(), DEC);
}

String ProcessRequest()
{
  return GetMillis();
}
```

```html
<!DOCTYPE html>
<html class="no-js" lang="">
   <head>
      <meta charset="utf-8">
      <meta http-equiv="x-ua-compatible" content="ie=edge">
      <title>ESP8266 WebSockets</title>
      <meta name="description" content="">
      <meta name="viewport" content="width=device-width, initial-scale=1">
   </head>
 
   <body>
    <h1>Millis</h1>
        <div id="counterDiv">---</div>
    </body>
  
    <script type="text/javascript" src="./js/main.js"></script>
</html>
```

```js
var counterDiv = document.getElementById('counterDiv');

function updateCounterUI(counter)
{
  counterDiv.innerHTML = counter; 
}

var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);

connection.onopen = function () {
  console.log('Connected: ');
  
  // Ejemplo 1, peticion desde cliente
  //(function scheduleRequest() {
  //  connection.send("");
  //  setTimeout(scheduleRequest, 100);
  //})();
};

connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};

connection.onmessage = function (e) {
  updateCounterUI(e.data);
  console.log('Server: ', e.data);
};

connection.onclose = function () {
  console.log('WebSocket connection closed');
};
```


