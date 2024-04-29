> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-dac/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Uso del DAC en el ESP32
```cpp
const int raw = 1500 * 255 / 3300;

void setup() {
  // Inicialización del DAC
  dacWrite(DAC1, raw); // Genera un voltaje de aproximadamente 1.5V en DAC1
}

void loop() {
  // No es necesario realizar nada en el bucle principal
}
```


## Generación de señales más complejas
```cpp
const int tableSize = 100;
const uint8_t sinTable[tableSize] = {127, 139, 150, ...}; // Valores precalculados

int index = 0;

void setup() {
  // Configuración del DAC
}

void loop() {
  // Generación de la señal
  dacWrite(DAC1, sinTable[index]);
  index = (index + 1) % tableSize;
  delay(10); // Controla la frecuencia de la onda
}
```


