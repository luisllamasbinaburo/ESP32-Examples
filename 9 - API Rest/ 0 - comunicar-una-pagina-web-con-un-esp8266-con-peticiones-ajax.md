> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/comunicar-una-pagina-web-con-un-esp8266-con-peticiones-ajax/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## comunicar-una-pagina-web-con-un-esp8266-con-peticiones-ajax
```cpp
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

#include "config.h"  // Sustituir con datos de vuestra red
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

String GetMillis()
{
  return String(millis(), DEC);
}

void InitServer()
{
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.on("/GetMillis", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", GetMillis());
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(400, "text/plain", "Not found");
  });

  server.begin();
    Serial.println("HTTP server started");
}
```

```html
<!DOCTYPE html>
<html class="no-js" lang="">
   <head>
      <meta charset="utf-8">
      <meta http-equiv="x-ua-compatible" content="ie=edge">
      <title>ESP8266 Ajax</title>
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

function ajaxCall() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
           if (xmlhttp.status == 200) {
              updateCounterUI(xmlhttp.responseText);
           }
           else {
              console.log('error', xmlhttp);
           }
        }
    };

    xmlhttp.open("GET", "GetMillis", true);
    xmlhttp.send();
}

(function scheduleAjax() {
    ajaxCall();
    setTimeout(scheduleAjax, 1000);
})();
```


