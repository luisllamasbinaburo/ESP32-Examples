> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-cambiar-frecuencia-procesador/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Cómo variar la frecuencia del CPU del ESP32
```cpp
// La función acepta las siguientes frecuencias como valores válidos:
// 240, 160, 80 <<< Para todos los tipos de cristal XTAL
// 40, 20, 10 <<< Para XTAL de 40MHz
// 26, 13 <<< Para XTAL de 26MHz
// 24, 12 <<< Para XTAL de 24MHz
bool setCpuFrequencyMhz(uint32_t cpu_freq_mhz);
```

```cpp
uint32_t getXtalFrequencyMhz(); // En MHz
```

```cpp
uint32_t getCpuFrequencyMhz(); // En MHz
```


## Ejemplo de código
```cpp
void setup() {
  Serial.begin(115200);

  // Establecer la frecuencia de la CPU a 80 MHz para optimización de consumo
  setCpuFrequencyMhz(80);

  // Imprimir la frecuencia del cristal XTAL
  Serial.print("Frecuencia del Cristal XTAL: ");
  Serial.print(getXtalFrequencyMhz());
  Serial.println(" MHz");

  // Imprimir la frecuencia de la CPU
  Serial.print("Frecuencia de la CPU: ");
  Serial.print(getCpuFrequencyMhz());
  Serial.println(" MHz");

  // Imprimir la frecuencia del bus APB
  Serial.print("Frecuencia del Bus APB: ");
  Serial.print(getApbFrequency());
  Serial.println(" Hz");
}

void loop() {
  // en este ejemplo aqui nada
}
```


