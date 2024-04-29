> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-light-sleep/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Uso del modo Light Sleep en el IDE de Arduino
```cpp
/**
 * @brief Enter light sleep with the configured wakeup options
 */
esp_err_t esp_light_sleep_start(void);
```


##  Uso del modo Light Sleep
```cpp
void setup() 
{
    Serial.begin(115200);
    delay(5000);
}

int counter = 0;

void loop() {
  Serial.println(counter);
  counter ++;

  esp_sleep_enable_timer_wakeup(2 * 1000000); //light sleep durante 2 segundos
  esp_light_sleep_start();  
}
```


