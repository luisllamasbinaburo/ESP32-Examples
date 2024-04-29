> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-timers/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Ejemplo de código
```cpp
hw_timer_t *timer = NULL;

volatiel void has_expired = false;
void IRAM_ATTR timerInterrupcion() {
 has_expired = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  timer = timerBegin(0, 80, true); // Timer 0, divisor de reloj 80
  timerAttachInterrupt(timer, &timerInterrupcion, true); // Adjuntar la función de manejo de interrupción
  timerAlarmWrite(timer, 1000000, true); // Interrupción cada 1 segundo
  timerAlarmEnable(timer); // Habilitar la alarma
}

void loop() {
  if(has_expired)
  {
     // Tareas a realizar cuando se activa la interrupción del Timer
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Alternar el estado del LED
    has_expired = false; 
  }
  
}
```


