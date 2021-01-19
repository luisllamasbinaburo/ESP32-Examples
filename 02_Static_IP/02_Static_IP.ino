#include <WiFi.h>
 
#include "config.h"  // Sustituir con datos de vuestra red
#include "ESP32_Utils.hpp"
  
void setup() 
{
  Serial.begin(115200);

  // Para modo STA
  ConnectWiFi_STA(true);

  // Para modo AP
  //ConnectWiFi_AP(true);
}
 
void loop() 
{
}
