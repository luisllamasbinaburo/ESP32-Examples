> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-sensor-hall-integrado/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Configuración del Sensor Hall
```cpp
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  // read hall effect sensor value
  int val = hallRead();
  
  // print the results to the serial monitor
  Serial.println(val); 
  delay(1000);
}
```


