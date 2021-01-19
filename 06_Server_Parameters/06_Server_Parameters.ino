#include <WiFi.h>
#include <WebServer.h>
 
#include "config.h"  // Sustituir con datos de vuestra red
#include "Server.hpp"
#include "ESP32_Utils.hpp"

void setup(void) 
{
   Serial.begin(115200);

   ConnectWiFi_STA();
   
   InitServer();
}
 
void loop()
{
   server.handleClient();
}
