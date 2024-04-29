#include <WiFi.h>
#include <ESPmDNS.h>
 
#include "config.h"  // Sustituir con datos de vuestra red
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_mDNS.hpp"
 
void setup()
{
   Serial.begin(115200);

   ConnectWiFi_STA();
   
   InitMDNS();
}
 
void loop()
{
}