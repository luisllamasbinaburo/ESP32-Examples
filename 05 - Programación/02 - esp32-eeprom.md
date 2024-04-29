> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-eeprom/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Configuración Inicial
```cpp
#include <EEPROM.h>
```

```cpp
void setup() {
  EEPROM.begin(size);
  // Resto del código de inicialización
}
```


## Almacenar y leer Datos
```cpp
int valor = 42;
int direccion = 0; // Dirección de memoria donde se almacenará el valor

EEPROM.write(direccion, valor); // Almacena el valor en la dirección dada
EEPROM.commit(); // Guarda los cambios en la memoria EEPROM

int valorLeido = EEPROM.read(direccion); // Lee el valor almacenado en la dirección dada
```


## Ejemplo de código
```cpp
#include <EEPROM.h>
#include <WiFi.h>

const char* ssid = "nombre-de-la-red";
const char* password = "contraseña-de-la-red";
int direccionSSID = 0;
int direccionPassword = sizeof(ssid);

void setup() {
  EEPROM.begin(512);
  EEPROM.writeString(direccionSSID, ssid);
  EEPROM.writeString(direccionPassword, password);
  EEPROM.commit();
  
  // Resto del código de inicialización, conexión a WiFi, etc.
}
```


## Funciones adicionales
```cpp
uint8_t readByte(int address);
int8_t readChar(int address);
uint8_t readUChar(int address);
int16_t readShort(int address);
uint16_t readUShort(int address);
int32_t readInt(int address);
uint32_t readUInt(int address);
int32_t readLong(int address);
uint32_t readULong(int address);
int64_t readLong64(int address);
uint64_t readULong64(int address);
float_t readFloat(int address);
double_t readDouble(int address);
bool readBool(int address);
size_t readString(int address, char* value, size_t maxLen);
String readString(int address);
size_t readBytes(int address, void * value, size_t maxLen);
template <class T> T readAll (int address, T &);

size_t writeByte(int address, uint8_t value);
size_t writeChar(int address, int8_t value);
size_t writeUChar(int address, uint8_t value);
size_t writeShort(int address, int16_t value);
size_t writeUShort(int address, uint16_t value);
size_t writeInt(int address, int32_t value);
size_t writeUInt(int address, uint32_t value);
size_t writeLong(int address, int32_t value);
size_t writeULong(int address, uint32_t value);
size_t writeLong64(int address, int64_t value);
size_t writeULong64(int address, uint64_t value);
size_t writeFloat(int address, float_t value);
size_t writeDouble(int address, double_t value);
size_t writeBool(int address, bool value);
size_t writeString(int address, const char* value);
size_t writeString(int address, String value);
size_t writeBytes(int address, const void* value, size_t len);
```


