> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-pwm/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Cómo usar una salida PWM el ESP32
```cpp
const int ledChannel = 0;    // Canal PWM, puede ser de 0 a 15
const int ledPin = 5;        // Pin al que está conectado el dispositivo
const int frequency = 5000;  // Frecuencia en Hz
const int resolution = 8;    // Resolución en bits (de 1 a 15)

ledcSetup(ledChannel, frequency, resolution);
```

```cpp
int dutyCycle = 128; // Valor del ciclo de trabajo (0 a 255)

ledcWrite(ledChannel, dutyCycle);
```


## Ejemplo de código
```cpp
const int ledChannel = 0;
const int ledPin = 5;
const int frequency = 5000;
const int resolution = 8;

void setup() {
  ledcSetup(ledChannel, frequency, resolution);
  ledcAttachPin(ledPin, ledChannel);
}

void loop() {
  // Incrementar el ciclo de trabajo gradualmente para aumentar la intensidad del LED
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(ledChannel, dutyCycle);
    delay(10);
  }

  // Disminuir el ciclo de trabajo gradualmente para reducir la intensidad del LED
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(ledChannel, dutyCycle);
    delay(10);
  }
}
```


## Alternativa con una librería
```cpp
#include <Arduino.h>
#include <analogWrite.h>

int brightStep = 1;
int brightness = 0;

void setup() {
  // Set resolution for a specific pin
  analogWriteResolution(LED_BUILTIN, 12);
}

void loop() {
  brightness += brightStep;
  if ( brightness == 0 || brightness == 255 ) {
    brightStep = -brightStep;
  }

  analogWrite(LED_BUILTIN, brightness);

  delay(10);
}
```


