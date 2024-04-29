> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/como-programar-esp32-con-el-ide-de-arduino/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Instalar ESP32 en IDE Arduino
```
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
```


## Hola mundo en el ESP32
```cpp
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // Configurar el pin del LED incorporado como salida
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // Encender el LED
  delay(1000); // Esperar un segundo
  digitalWrite(LED_BUILTIN, LOW); // Apagar el LED
  delay(1000); // Esperar un segundo
}
```


