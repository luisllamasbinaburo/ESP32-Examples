> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-random-numbers/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Cómo generar números aleatorios en ESP32
```cpp
void setup()
{
  Serial.begin(115200);
}

void loop() 
{ 
  auto randomNumber = esp_random();   
  Serial.println(randomNumber); 
  delay(2000);
}
```

```cpp
void setup() 
{
  Serial.begin(115200);
}
 
void loop() 
{ 
  auto randomNumber0_10 = random(10); // numero aleatorio entre 0-10
  auto randomNumber10_20 = random(10, 20); // numero aleatorio entre 10-20
  Serial.println(randomNumber0_10);     
  Serial.println(randomNumber10_20);
 
  delay(1000);
}
```


