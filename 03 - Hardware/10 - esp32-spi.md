> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-spi/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## El bus SPI en el ESP32
```cpp
void setup() {
  // Inicializar comunicación SPI
  SPI.begin();
}
```

```cpp
SPIClass vspi = SPIClass(VSPI);

MySPI.begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);
```


## Enviar Datos
```cpp
byte dataToSend = 0xAA;
byte receivedData;

digitalWrite(SS, LOW);  // Bajar línea CS/SS para seleccionar el dispositivo
receivedData = SPI.transfer(dataToSend);  // Enviar y recibir datos
digitalWrite(SS, HIGH); // Subir línea CS/SS para finalizar la comunicación
```


## Usando múltiples SPI en el ESP32
```cpp
#include <SPI.h>

#define HSPI 2  // 2 para S2 y S3, 1 para S1
#define VSPI 3

// reemplazar por los pines que queráis usar
const int HSPI_MISO = 0;
const int HSPI_MOSI = 0;
const int HSPI_SCLK = 0;
const int HSPI_SS = 0;

const int VSPI_MISO = 0;
const int VSPI_MOSI = 0;
const int VSPI_SCLK = 0;
const int VSPI_SS = 0;

SPIClass vspi = SPIClass(VSPI);
SPIClass hspi = SPIClass(HSPI);

void setup()
{ 
  vspi.begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);
  hspi.begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS);
}

void loop()
{
  delay(1000);  // do nothing
}
```


