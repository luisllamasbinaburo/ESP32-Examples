> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/comunicar-una-pagina-web-con-asyncwebsockets-en-el-esp8266/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## comunicar-una-pagina-web-con-asyncwebsockets-en-el-esp8266
```cpp
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <WebSocketsServer.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "Websocket.hpp"
#include "Server.hpp"
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_AWS.hpp"

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
  // Ejemplo 2, llamada desde servidor
  ws.textAll(GetMillis());
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
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){ 
  if(type == WS_EVT_CONNECT){
    //Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->printf("Hello Client %u :)", client->id());
    client->ping();
  } else if(type == WS_EVT_DISCONNECT){
    //Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } else if(type == WS_EVT_ERROR){
    //Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if(type == WS_EVT_PONG){
    //Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
  } else if(type == WS_EVT_DATA){
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    String msg = "";
    if(info->final && info->index == 0 && info->len == len){
      if(info->opcode == WS_TEXT){
        for(size_t i=0; i < info->len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }

      if(info->opcode == WS_TEXT)
      ProcessRequest(client, msg);
      
    } else {
      //message is comprised of multiple frames or the frame is split into multiple packets
      if(info->opcode == WS_TEXT){
        for(size_t i=0; i < len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
      Serial.printf("%s\n",msg.c_str());

      if((info->index + len) == info->len){
        if(info->final){
          if(info->message_opcode == WS_TEXT)
          ProcessRequest(client, msg);
        }
      }
    }
  }
}

void InitWebSockets()
{
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  Serial.println("WebSocket server started");
}
```

```cpp
AsyncWebSocket ws("/ws");

String GetMillis()
{
  return String(millis(), DEC);
}

void ProcessRequest(AsyncWebSocketClient * client, String request)
{
  String response = GetMillis();
  client->text(response);
}
```

```html
<!DOCTYPE html>
<html class="no-js" lang="">
   <head>
      <meta charset="utf-8">
      <meta http-equiv="x-ua-compatible" content="ie=edge">
      <title>ESP8266 Websocket Async</title>
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

```cpp
var myDiv = document.getElementById('counterDiv');

function updateCounterUI(counter)
{
  myDiv.innerHTML = counter; 
}

var connection = new WebSocket('ws://' + location.hostname + '/ws', ['arduino']);

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


