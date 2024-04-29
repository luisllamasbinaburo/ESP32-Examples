> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-servo/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

##  Incluir la biblioteca Servo
```cpp
// para la librermadhephaestus
#include <Servo.h>

// para la libreria RoboticsBrno
#include <ESP32Servo.h>
```


## Crear un objeto Servo
```cpp
Servo miServo;
```


## Configurar el pin del servo
```cpp
const int pinServo = 18; // Pin GPIO al que está conectado el servo

void setup() 
{
  miServo.attach(pinServo);
}
```


## Controlar el servo
```cpp
void loop() 
{
  miServo.write(0);    // Mover el servo a 0 grados
  delay(1000);         // Esperar 1 segundo
  miServo.write(90);   // Mover el servo a 90 grados
  delay(1000);         // Esperar 1 segundo
  miServo.write(180);  // Mover el servo a 180 grados
  delay(1000);         // Esperar 1 segundo
}
```


