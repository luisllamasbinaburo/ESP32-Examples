> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/como-servir-y-consumir-un-api-rest-con-esp8266-y-axios/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## como-servir-y-consumir-un-api-rest-con-esp8266-y-axios
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

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void InitServer()
{
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  
  server.on("/item", HTTP_GET, getRequest);
  server.on("/item", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, postRequest);
  server.on("/item", HTTP_PUT, [](AsyncWebServerRequest * request){}, NULL, putRequest);
  server.on("/item", HTTP_PATCH, [](AsyncWebServerRequest * request){}, NULL, patchRequest);
  server.on("/item", HTTP_DELETE, deleteRequest);
  
  server.onNotFound(notFound);

  server.begin();
    Serial.println("HTTP server started");
}
```

```cpp
#include "ESP8266_Utils_APIREST.hpp"

const char* PARAM_FILTER = "filter";

void getAll(AsyncWebServerRequest *request)
{
  String message = "Get All";
  Serial.println(message);
  request->send(200, "text/plain", message);
}

void getFiltered(AsyncWebServerRequest *request)
{
  String message = "Get filtered by " + request->getParam(PARAM_FILTER)->value();
  Serial.println(message);
  request->send(200, "text/plain", message);
}

void getById(AsyncWebServerRequest *request)
{
  int id = GetIdFromURL(request, "/item/");

  String message = String("Get by Id ") + id;
  Serial.println(message);
  request->send(200, "text/plain", message);
}

void getRequest(AsyncWebServerRequest *request) {
  
  if (request->hasParam(PARAM_FILTER)) {
    getFiltered(request);
  }
  else if(request->url().indexOf("/item/") != -1)
  {
    getById(request);
  }
  else {
    getAll(request);
  }
}

void postRequest(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{ 
  String bodyContent = GetBodyContent(data, len);
  
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) { request->send(400); return;}

  String string_data = doc["data"];
  String message = "Create " + string_data;
  Serial.println(message);
  request->send(200, "text/plain", message);
}

void patchRequest(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{
  int id = GetIdFromURL(request, "/item/");
  String bodyContent = GetBodyContent(data, len);
  
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) { request->send(400); return;}

  String string_data = doc["data"];
  String message = String("Update ") + id + " with " + string_data;
  Serial.println(message);
  request->send(200, "text/plain", message);
}

void putRequest(AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total)
{
  int id = GetIdFromURL(request, "/item/");
  String bodyContent = GetBodyContent(data, len);
   
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, bodyContent);
  if (error) { request->send(400); return;}

  String string_data = doc["data"];
  String message = String("Replace ") + id + " with " + string_data;
  Serial.println(message);
  request->send(200, "text/plain", message);
}

void deleteRequest(AsyncWebServerRequest *request) {
  int id = GetIdFromURL(request, "/item/");

  String message = String("Delete ") + id;
  Serial.println(message);
  request->send(200, "text/plain", message);
}
```

```html
<!DOCTYPE html>
<html>
  <head>
    <title>ESP8266 Axios</title>
    <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <div>
            <div>
                <button onclick="getAllRequest()">Get All</button>
                <button onclick="getFilteredRequest()">Get Filtered</button>
                <button onclick="getByIdRequest()">Get by Id</button>
            </div>
            <div>
                <button onclick="postRequest()">Create</button>
            </div>
            <div>
                <button onclick="patchRequest()">Update</button>
            </div>
            <div>
                <button onclick="putRequest()">Replace</button>
            </div>
            <div>
                <button onclick="deleteRequest()">Delete</button>
            </div>
        </div>
        
        <!-- Desde CDN -->
        <!--<script src="https://cdn.jsdelivr.net/npm/axios@0.18.0/dist/axios.min.js"></script>-->
        <script type="text/javascript" src="./vendor/axios.min.js"></script>

        <script src="./js/API.js"></script>
    </body>
</html>
```

```js
function getAllRequest()
{
  axios.get('item')
    .then(function (response) {
    console.log(response);
    })
    .catch(function (error) {
    console.log(error);
    })
    .then(function () {
    });
}

function getFilteredRequest()
{
  axios.get('item', {
    params: {
      filter : 'myFilter'
    }
    })
    .then(function (response) {
    console.log(response);
    })
    .catch(function (error) {
    console.log(error);
    })
    .then(function () {
    });
}

function getByIdRequest()
{
  id = 10;
  axios.get('item/' + id)
    .then(function (response) {
    console.log(response);
    })
    .catch(function (error) {
    console.log(error);
    })
    .then(function () {
    });
}

function postRequest()
{
  axios.post('item', {
    data: 'NewItem'
    })
    .then(function (response) {
    console.log(response);
    })
    .catch(function (error) {
    console.log(error);
    })
    .then(function () {
    });
}

function putRequest()
{
  id = 10;
  axios.put('item/' + id, {
    data: 'NewItem'
    })
    .then(function (response) {
    console.log(response);
    })
    .catch(function (error) {
    console.log(error);
    })
    .then(function () {
    });
}

function patchRequest()
{
  id = 10;
  axios.patch('item/' + id, {
    data: 'NewItem'
    })
    .then(function (response) {
    console.log(response);
    })
    .catch(function (error) {
    console.log(error);
    })
    .then(function () {
    });
}

function deleteRequest()
{
  id = 10;
  axios.delete('item/' + id)
    .then(function (response) {
    console.log(response);
    })
    .catch(function (error) {
    console.log(error);
    })
    .then(function () {
    });
}
```


