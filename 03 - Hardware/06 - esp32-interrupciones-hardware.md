> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-interrupciones-hardware/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Definir la función de callback (ISR)
```cpp
void IRAM_ATTR miFuncionInterrupcion() {
  // Aquí puedes agregar el código que se ejecutará cuando ocurra la interrupción
}
```


## 3. Configurar la interrupción
```cpp
const int pinInterrupcion = 12; // Pin GPIO donde configurar la interrupción

void setup() {
  pinMode(pinInterrupcion, INPUT_PULLUP); // Configurar el pin como entrada con resistencia pull-up interna
  attachInterrupt(digitalPinToInterrupt(pinInterrupcion), miFuncionInterrupcion, RISING); // Configurar la interrupción
}
```


## 4. Desactivar la interrupción (opcional)
```cpp
detachInterrupt(digitalPinToInterrupt(pinInterrupcion)); // Desactivar la interrupción
```


## Ejemplo de código
```cpp
const int pinBoton = 12; // Pin GPIO donde está conectado el botón

volatile bool has_interruped = false;
void IRAM_ATTR miFuncionInterrupcion() {
  has_interrupted = true;
}

void setup() 
{
  Serial.begin(115200);
  pinMode(pinBoton, INPUT_PULLUP); // Configurar el pin como entrada con resistencia pull-up interna
  attachInterrupt(digitalPinToInterrupt(pinBoton), miFuncionInterrupcion, RISING); // Configurar la interrupción
}

void loop() 
{
  if(has_interrupted)
  {
    Serial.println("¡Botón presionado!");
    has_interrupted = false;
  }
}
```


