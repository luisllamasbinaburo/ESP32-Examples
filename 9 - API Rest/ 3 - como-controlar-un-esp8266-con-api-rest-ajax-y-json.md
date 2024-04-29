> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/como-controlar-un-esp8266-con-api-rest-ajax-y-json/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## como-controlar-un-esp8266-con-api-rest-ajax-y-json
```cpp
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <ArduinoJson.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "API.hpp"
#include "Server.hpp"
#include "ESP8266_Utils.hpp"

void setup(void)
{
  Serial.begin(115200);
  SPIFFS.begin();
  
  ConnectWiFi_STA();

  InitServer();
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

    server.on("/LED", HTTP_GET, getData);
    server.on("/LED", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, setData);
  
    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(400, "text/plain", "Not found");
    });

    server.begin();
    Serial.println("HTTP server started");
}
```

```cpp
#include "ESP8266_Utils_APIREST.hpp"

void getData(AsyncWebServerRequest *request)
{
   AsyncResponseStream *response = request->beginResponseStream("application/json");
    
   // obtendríamos datos de GPIO, estado...
   StaticJsonDocument<300> jsonDoc;
   jsonDoc["id"] = random(0,10);
   jsonDoc["status"] = random(0,2);
   serializeJson(jsonDoc, *response);
   
   request->send(response);
}

void setData(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{
  String bodyContent = GetBodyContent(data, len);

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) { request->send(400); return;}
 
  int id = doc["id"];
  bool ledStatus = doc["status"];
  Serial.println(id);
  Serial.println(ledStatus);
  // hacer acciones con los datos recibidos

  request->send(200);
}
```

```html
<!DOCTYPE html>
<html class="no-js" lang="">
   <head>
      <meta charset="utf-8">
      <meta http-equiv="x-ua-compatible" content="ie=edge">
      <title>ESP8266 Json Ajax</title>
      <meta name="description" content="">
      <meta name="viewport" content="width=device-width, initial-scale=1">
   </head>
 
   <body>
     <div>
      Value:<br>
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
function sendData()
{
  var xhttp = new XMLHttpRequest();

  let ledNumber = document.getElementById('ledNumber');
  let ledStatus = document.querySelector('input[name="status"]:checked');
  let ledData = {
    id: ledNumber.value,
    status: ledStatus.value
  }
  let data = JSON.stringify(ledData);

  xhttp.addEventListener('load', function(event) {
    console.log('OK', xhttp);
  });

  xhttp.addEventListener('error', function(event) {
    console.log('error', xhttp);
  });

  xhttp.open('POST', 'LED');
  xhttp.setRequestHeader('Content-Type', 'application/json');
  xhttp.send(data);
}

function getData()
{
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function() {
        if (xhttp.readyState == XMLHttpRequest.DONE) {
           if (xhttp.status == 200) {
        console.log((xhttp.responseText));
        let json = JSON.parse(xhttp.responseText);
              console.log();
        
        let receivedMsg = 'Received: GPIO ' + json.id + ' ' + (json.status == 1 ? "ON" : "OFF");
        document.getElementById('receivedText').textContent = receivedMsg;
           }
           else {
              console.log('error', xhttp);
           }
        }
    };

    xhttp.open("GET", "LED", true);
    xhttp.send();
}
```


