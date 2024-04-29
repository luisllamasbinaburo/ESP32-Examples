> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-uart/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Cómo usar el UART en el ESP32 en el entorno de Arduino
```cpp
Serial.println("¡Hola, UART!");
```


## Usando múltiples UART en el ESP32
```cpp
include <HardwareSerial.h>

HardwareSerial MySerial(1); // definir un Serial para UART1
const int MySerialRX = 16;
const int MySerialTX = 17;

void setup() 
{
	// inicializar el Serial a los pines
    MySerial.begin(11500, SERIAL_8N1, MySerialRX, MySerialTX);
}

void loop() 
{
	// aqui podríamos usar nuestro MySerial con normalidad
    while (MySerial.available() > 0) {
        uint8_t byteFromSerial = MySerial.read();
        //y lo que sea
    }
   
    MySerial.write(...);
}
```


