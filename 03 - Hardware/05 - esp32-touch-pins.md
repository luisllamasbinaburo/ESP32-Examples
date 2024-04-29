> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-touch-pins/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Cómo leer los pines táctiles del ESP32
```cpp
touchRead(int pin);
```


## Lectura de pines táctiles
```cpp
const int touchPin0 = 4;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 - Touch Raw Test");
}

void loop() {
  auto touch0raw = touchRead(touchPin0); // realizar la lectura
  Serial.println(touch0raw);  
  delay(1000);
}
```


## Lectura de pines táctiles con umbral
```cpp
const int touchPin0 = 4;
const int touchThreshold = 40; // Umbral del sensor

void setup() {
    Serial.begin(115200);
    delay(1000); // Delay to launch the serial monitor
    Serial.println("ESP32 - Touch Threshold Demo");
}

void loop() {
	auto touch0raw = touchRead(touchPin0); // realizar la lectura   
    
    if(touch0raw < touchThreshold )
    {
        Serial.println("Toque detectado");
    }
    delay(500);
}
```


## Lectura pines táctiles con interrupciones
```cpp
int threshold = 40;
volatile bool touch1detected = false;

void gotTouch1(){
 touch1detected = true;
}

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  
  Serial.println("ESP32 Touch Interrupt Test");
  touchAttachInterrupt(T2, gotTouch1, threshold);
}

void loop(){
  if(touch1detected)
  {
    touch1detected = false;
    Serial.println("Touch 1 detected");
  }
}
```


