> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/como-emplear-un-esp8266-como-cliente-de-un-api-rest-con-json/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## como-emplear-un-esp8266-como-cliente-de-un-api-rest-con-json
```cpp
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "API.hpp"
#include "ESP8266_Utils.hpp"

void setup() 
{
  Serial.begin(115200);
  
   ConnectWiFi_STA();
  
  GetAll();
  GetItem(1);
  GetQuery("ABC");
  Create("New item");
  ReplaceById(2, "New item");
    UpdateById(2, "New item");
  DeleteById(5);
}

void loop() 
{
}
```

```cpp
String ApiHost = "http://192.168.1.1:8080";

void processResponse(int httpCode, HTTPClient& http)
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

void GetAll()
{
  HTTPClient http;
  http.begin(ApiHost + "/item");
  int httpCode = http.GET();
  processResponse(httpCode, http);
}

void GetItem(int id)
{
  HTTPClient http;
  http.begin(ApiHost + "/item/" + id);
  int httpCode = http.GET();
  processResponse(httpCode, http);
}

void GetQuery(String filter)
{
  HTTPClient http;
  http.begin(ApiHost + "/item?filter=" + filter);
  int httpCode = http.GET();
  processResponse(httpCode, http);
}

void Create(String newData)
{
  HTTPClient http;
  http.begin(ApiHost + "/item");
  http.addHeader("Content-Type", "application/json");
  
  String message = "";
  StaticJsonDocument<300> jsonDoc;
  jsonDoc["data"] = newData;
  serializeJson(jsonDoc, message);
  
  int httpCode = http.POST(message);
  processResponse(httpCode, http);
}

void ReplaceById(int id, String newData)
{
  HTTPClient http;
  http.begin(ApiHost + "/item/" + id);
  http.addHeader("Content-Type", "application/json");

  String message = "";
  StaticJsonDocument<300> jsonDoc;
  jsonDoc["data"] = newData;
  serializeJson(jsonDoc, message);

  int httpCode = http.PUT(message);
  processResponse(httpCode, http);
}

void UpdateById(int id, String newData)
{
  HTTPClient http;
  http.begin(ApiHost + "/item/" + id);
  http.addHeader("Content-Type", "application/json");
  
  String message = "";
  StaticJsonDocument<300> jsonDoc;
  jsonDoc["data"] = newData;
  serializeJson(jsonDoc, message);
  
  int httpCode = http.PATCH(message);
  processResponse(httpCode, http);
}

void DeleteById(int id)
{
  HTTPClient http;
  http.begin(ApiHost + "/item/" + id);
  int httpCode = http.sendRequest("DELETE");
  processResponse(httpCode, http);
}
```


