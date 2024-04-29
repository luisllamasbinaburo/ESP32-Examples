> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/crear-un-interface-web-para-controlar-el-esp8266/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa


## crear-un-interface-web-para-controlar-el-esp8266
```cpp
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <ArduinoJson.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "API.hpp"
#include "WebSockets.hpp"
#include "Server.hpp"
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_AWS.hpp"
#include "ReactiveArduinoLib.h"

auto obsD0 = Reactive::FromDigitalInput(D0);
auto obsD5 = Reactive::FromDigitalInput(D5);
auto obsD6 = Reactive::FromDigitalInput(D6);
auto obsD7 = Reactive::FromDigitalInput(D7);

void setup(void)
{
  Serial.begin(115200);
  SPIFFS.begin();

  ConnectWiFi_STA();

  InitServer();
  InitWebSockets();

  obsD0.Distinct().Do([](int i) { updateGPIO("D0", i); });
  obsD5.Distinct().Do([](int i) { updateGPIO("D5", i); });
  obsD6.Distinct().Do([](int i) { updateGPIO("D6", i); });
  obsD7.Distinct().Do([](int i) { updateGPIO("D7", i); });
}

void loop(void)
{
  obsD0.Next();
  obsD5.Next();
  obsD6.Next();
  obsD7.Next();
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
void setGPIO(String id, bool state)
{
   Serial.print("Set GPIO ");
   Serial.print(id);
   Serial.print(": ");
   Serial.println(state);
}

void setPWM(String id, int pwm)
{
   Serial.print("Set PWM ");
   Serial.print(id);
   Serial.print(": ");
   Serial.println(pwm);
}

void doAction(String actionId)
{
   Serial.print("Doing action: ");
   Serial.println(actionId);
}
```

```cpp
AsyncWebSocket ws("/ws");

void ProcessRequest(AsyncWebSocketClient *client, String request)
{
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  if (error) { return; }
  
  String command = doc["command"];
  if(command == "setGPIO") 
    setGPIO(doc["id"], (bool)doc["status"]);
  else if(command == "setPWM")
    setPWM(doc["id"], (int)doc["pwm"]);
  else if(command == "doAction")
    doAction(doc["id"]);
}

void updateGPIO(String input, bool value)
{
  String response;
  StaticJsonDocument<300> doc;
  doc["command"] = "updateGPIO";
  doc["id"] = input;
  doc["status"] = value ? String("ON") : String("OFF");
  serializeJson(doc, response);

  ws.textAll(response);

  Serial.print(input);
  Serial.println(value ? String(" ON") : String(" OFF"));
}
```

```html
<!DOCTYPE html>
<html class="no-js" lang="">

<head>
    <title>ESP8266 Async GPIO</title>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">

    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>

<body>
    <link rel="stylesheet" href="vendor/google-fonts.css">
    <link rel="stylesheet" href="vendor/material.css">
    <link rel="stylesheet" href="css/main.css">

    <div class="mdl-card mdl-shadow--2dp">
        <div class="mdl-card__title mdl-card--expand">
            <h2 class="mdl-card__title-text">Async GPIO</h2>
        </div>

        <div class="mdl-card__supporting-text">
            <h6>Input example:</h6>
            <ul class="mdl-list mdl-shadow--2dp">
                <li class="mdl-list__item">
                    <span class="mdl-list__item-primary-content">D0</span>
                    <span class="mdl-list__item-secondary-action">
                        <label id="input-label-D0" class="label-big Off-style">OFF</label>
                    </span>
                </li>
                <li class="mdl-list__item">
                    <span class="mdl-list__item-primary-content">D5</span>
                    <span class="mdl-list__item-secondary-action">
                        <label id="input-label-D5" class="label-big Off-style">OFF</label>
                    </span>
                </li>
                <li class="mdl-list__item">
                    <span class="mdl-list__item-primary-content">D6</span>
                    <span class="mdl-list__item-secondary-action">
                        <label id="input-label-D6" class="label-big Off-style">OFF</label>
                    </span>
                </li>
                <li class="mdl-list__item">
                    <span class="mdl-list__item-primary-content">D7</span>
                    <span class="mdl-list__item-secondary-action">
                        <label id="input-label-D7" class="label-big Off-style">OFF</label>
                    </span>
                </li>
            </ul>
        </div>

        <div class="mdl-card__supporting-text">
            <h6>Ouput example:</h6>
            <ul class="mdl-list mdl-shadow--2dp">
                <li class="mdl-list__item">
                    <span class="mdl-list__item-primary-content">D8</span>
                    <span class="mdl-list__item-secondary-action">
                        <label class="mdl-switch mdl-js-switch mdl-js-ripple-effect">
                            <input id="output-switch-D8" data-id="D8" type="checkbox" class="mdl-switch__input" checked 
                            onchange="sendGPIO(this.dataset.id, this.checked)"/>
                        </label>
                    </span>
                </li>
                <li class="mdl-list__item">
                    <span class="mdl-list__item-primary-content">D9</span>
                    <span class="mdl-list__item-secondary-action">
                        <label class="mdl-switch mdl-js-switch mdl-js-ripple-effect">
                            <input id="output-switch-D9" data-id="D9" type="checkbox" class="mdl-switch__input" checked 
                            onchange="sendGPIO(this.dataset.id, this.checked)"/>
                        </label>
                    </span>
                </li>
                <li class="mdl-list__item">
                    <span class="mdl-list__item-primary-content">D10</span>
                    <span class="mdl-list__item-secondary-action">
                        <label class="mdl-switch mdl-js-switch mdl-js-ripple-effect">
                            <input id="output-switch-D10" data-id="D10" type="checkbox" class="mdl-switch__input" checked 
                            onchange="sendGPIO(this.dataset.id, this.checked)"/>
                        </label>
                    </span>
                </li>
                <li class="mdl-list__item">
                    <span class="mdl-list__item-primary-content">D10</span>
                    <span class="mdl-list__item-secondary-action">
                        <div class="mdl-grid">
                            <div class="mdl-cell mdl-cell--10-col">
                                <input id="slider-pwm-1" data-id="1" class="mdl-slider mdl-js-slider"
                                    type="range" min="0" max="255" value="25"
                                    onchange="sendPWM(this.dataset.id, this.value);" >
                            </div>
                            <div class="mdl-cell mdl-cell--2-col">
                                <input id="slider-text-pwm-1" data-id="1" style="width:35px;"
                                onchange="sendPWM(this.dataset.id, this.value);" value="25"></input>
                            </div>
                        </div>
                    </span>
                </li>
            </ul>
        </div>

        <div class="mdl-card__supporting-text ">
            <div>
                <h6>Example</h6>
                <button class="mdl-button mdl-js-button mdl-button--primary mdl-js-ripple-effect" style="width: 160px;"
                    data-id="action-1" onclick="sendAction(this.dataset.id)">
                    Do something
                </button>
            </div>
        </div>
    </div>
</body>

<script type="text/javascript" src="./js/main.js"></script>
<script type="text/javascript" src="vendor/material.js"></script>
</html>
```

```js
var connection = new WebSocket('ws://' + location.hostname + '/ws', ['arduino']);

connection.onopen = function () {
  connection.send('Received from Client');
  console.log('Connected');
};

connection.onerror = function (error) {
  console.log('WebSocket Error', error);
};

connection.onmessage = function (e) {
    console.log('Received from server: ', e.data);
    processReceived(e.data);
};

connection.onclose = function () {
  console.log('WebSocket connection closed');
};

function processReceived(data)
{
  json = JSON.parse(data)
  if(json.command == 'updateGPIO')
  {
    updateGPIO(json.id, json.status);
  }
}

function sendGPIO(id, status)
{
  let data = {
    command : "setGPIO",
    id: id,
    status: status
  }

  let json = JSON.stringify(data);
  connection.send(json);
}

function sendPWM(id, pwm)
{
  updateSliderText(id, pwm);

  let data = {
    command : "setPWM",
    id: id,
    pwm: pwm
  }

  let json = JSON.stringify(data);
  connection.send(json);
}

function sendAction(id)
{
  let data = {
    command : "doAction",
    id: id,
  }

  let json = JSON.stringify(data);
  connection.send(json);
}

function updateGPIO(id, status)
{
    document.getElementById('input-label-' + id).textContent = status;

  if(status == 'ON')
  {
        document.getElementById('input-label-' + id).classList.add('On-style');
    document.getElementById('input-label-' + id).classList.remove('Off-style');
  }
  else
    {
    document.getElementById('input-label-' + id).classList.add('Off-style');
    document.getElementById('input-label-' + id).classList.remove('On-style');
  }
}

function updateSliderText(id, value) {
  document.getElementById('slider-pwm-' + id).value = value; 
  document.getElementById('slider-text-pwm-'+ id).value = value; 
  }
```

```css
.label-big {
  border-radius: 3px;
    font-size: 16px;
    font-weight: 600;
    line-height: 2;
    padding: 0 8px;
    transition: opacity .2s linear;
    color: #fff
}

.On-style {
  background-color: #006b75;
}

.Off-style {
  background-color: #b60205;
}
```


