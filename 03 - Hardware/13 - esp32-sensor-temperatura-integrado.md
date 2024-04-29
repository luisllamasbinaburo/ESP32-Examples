> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-sensor-temperatura-integrado/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Lectura de la Temperatura
```cpp
void setup() {
  Serial.begin(115200);
}

void loop() {
  float temp_celsius = temperatureRead();

  Serial.print("Temp onBoard ");
  Serial.print(temp_celsius);
  Serial.println("°C");

  delay(1000);
}
```


