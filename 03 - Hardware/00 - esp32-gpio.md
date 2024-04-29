> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-gpio/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Configurar un pin como entrada y leer su valor
```cpp
const int sensorPin = 13; // Ejemplo de pin para sensor
int sensorValue;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = digitalRead(sensorPin);
  Serial.println(sensorValue);
  delay(1000);
}
```


## Uso de una entrada digital en el ESP32
```cpp
const int buttonPin = 12;  // Pin para el botón
int buttonState;            // Variable para almacenar el estado del botón

void setup() {
  pinMode(buttonPin, INPUT);  // Configurar el pin como entrada
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);  // Leer el estado del botón
  Serial.println(buttonState);            // Imprimir el estado en el puerto serie
  delay(100);                             // Pequeña pausa para evitar lecturas erráticas
}
```


## Uso de una salida digital en el ESP32
```cpp
const int ledPin = 13;  // Pin para el LED
int ledState = LOW;     // Estado inicial del LED

void setup() {
  pinMode(ledPin, OUTPUT);  // Configurar el pin como salida
  Serial.begin(9600);
}

void loop() {
  digitalWrite(ledPin, ledState);  // Establecer el estado del LED
  Serial.println(ledState);         // Imprimir el estado en el puerto serie
  delay(1000);                      // Esperar un segundo
  ledState = !ledState;            // Cambiar el estado del LED
}
```


## Configurar un botón con resistencia pull-up interna
```cpp
const int buttonPin = 12;
int buttonState;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    Serial.println("Botón presionado");
  }
  delay(100);
}
```


