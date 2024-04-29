#include <WiFi.h>
#include <HTTPClient.h>

String url = "http://www.google.com";
 
#include "config.h"  // Sustituir con datos de vuestra red
#include "Client.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_Client.hpp"
 
void setup()
{
   Serial.begin(115200);
 
   ConnectWiFi_STA();
}
 
void loop()
{
   ClientRequest();
 
   delay(30000);
}
