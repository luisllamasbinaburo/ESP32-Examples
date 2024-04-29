> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-deep-sleep/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Guardar Datos en Memorias RTC
```cpp
RTC_DATA_ATTR int bootCount = 0;
```


## Stub wake
```cpp
void RTC_IRAM_ATTR esp_wake_deep_sleep() {
    esp_default_wake_deep_sleep();
    // add additional functionality here
}
```


## Uso del modo Deep Sleep en el IDE de Arduino
```cpp
#include <esp_sleep.h>
```

```cpp
esp_sleep_enable_timer_wakeup(5 * 1000000);
esp_deep_sleep_start();
```

```cpp
/**
 * @brief Enter deep-sleep mode
 *
 * The device will automatically wake up after the deep-sleep time
 * Upon waking up, the device calls deep sleep wake stub, and then proceeds to load application.
 */
void esp_deep_sleep(uint64_t time_in_us) __attribute__((noreturn));
```


##  Uso del modo Deep Sleep
```cpp
void setup()
{
  Serial.begin(115200);
  Serial.println("Iniciando...");
   
  esp_deep_sleep(2 * 1000000);  // entrar en deep sleep por 10 segundos
  
  // Esta función nunca se ejecutará debido al modo Deep Sleep
}

void loop()
{
  // Esta función nunca se ejecutará debido al modo Deep Sleep
}
```


##  Uso de la memoria del RTC
```cpp
RTC_DATA_ATTR int bootCount = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Iniciando...");
   
  bootCount++;
  Serial.println(bootCount);
  esp_deep_sleep(2 * 1000000);  // entrar en deep sleep por 10 segundos
  
  // Esta función nunca se ejecutará debido al modo Deep Sleep
}

void loop()
{
  // Esta función nunca se ejecutará debido al modo Deep Sleep
}
```


##  Uso de la función wake stub
```cpp
RTC_DATA_ATTR int bootCount = 0;

void RTC_IRAM_ATTR esp_wake_deep_sleep() {
    esp_default_wake_deep_sleep();
    bootCount++;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Iniciando...");
     
  Serial.println(bootCount);
  esp_deep_sleep(2 * 1000000);  // entrar en deep sleep por 10 segundos  
}

void loop()
{
  // Esta función nunca se ejecutará debido al modo Deep Sleep
}
```


