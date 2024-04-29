> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-preferences/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Incluir la biblioteca
```cpp
#include <Preferences.h>
```


## Crear un objeto `Preferences`
```cpp
Preferences preferences;
```


## Inicializar y abrir el espacio de almacenamiento
```cpp
bool begin(const char * name, bool readOnly=false, const char* partition_label=NULL)
```

```cpp
preferences.begin("mis_variables", false);
```


## Almacenar y recuperar valores
```cpp
// Almacenar un entero
preferences.putInt("valor_entero", 42);

// Recuperar un entero
int miEntero = preferences.getInt("valor_entero", 0); // El segundo argumento es el valor predeterminado si no se encuentra la preferencia

// Almacenar un valor flotante
preferences.putFloat("valor_flotante", 3.14);

// Recuperar un valor flotante
float miFlotante = preferences.getFloat("valor_flotante", 0.0);
```


## Eliminar una variable
```cpp
bool remove("mi_variable");
```


## Cerrar el espacio de almacenamiento
```cpp
preferences.end();
```


## Ejemplo de código
```cpp
#include <Preferences.h>
#include <WiFi.h>

const char* ssid = "nombre-de-la-red";
const char* password = "contraseña-de-la-red";

Preferences preferences;

void setup() {
  preferences.begin("mis_variables", false);
  preferences.putString("nombre_red", ssid);
  preferences.putString("password_red", password);
  preferences.end();
  
  // Resto del código de inicialización, conexión a WiFi, etc.
}
```


## Funciones adicionales
```cpp
bool begin(const char * name, bool readOnly=false, const char* partition_label=NULL);
void end();

bool clear();
bool remove(const char * key);

size_t putChar(const char* key, int8_t value);
size_t putUChar(const char* key, uint8_t value);
size_t putShort(const char* key, int16_t value);
size_t putUShort(const char* key, uint16_t value);
size_t putInt(const char* key, int32_t value);
size_t putUInt(const char* key, uint32_t value);
size_t putLong(const char* key, int32_t value);
size_t putULong(const char* key, uint32_t value);
size_t putLong64(const char* key, int64_t value);
size_t putULong64(const char* key, uint64_t value);
size_t putFloat(const char* key, float_t value);
size_t putDouble(const char* key, double_t value);
size_t putBool(const char* key, bool value);
size_t putString(const char* key, const char* value);
size_t putString(const char* key, String value);
size_t putBytes(const char* key, const void* value, size_t len);

bool isKey(const char* key);

PreferenceType getType(const char* key);
int8_t getChar(const char* key, int8_t defaultValue = 0);
uint8_t getUChar(const char* key, uint8_t defaultValue = 0);
int16_t getShort(const char* key, int16_t defaultValue = 0);
uint16_t getUShort(const char* key, uint16_t defaultValue = 0);
int32_t getInt(const char* key, int32_t defaultValue = 0);
uint32_t getUInt(const char* key, uint32_t defaultValue = 0);
int32_t getLong(const char* key, int32_t defaultValue = 0);
uint32_t getULong(const char* key, uint32_t defaultValue = 0);
int64_t getLong64(const char* key, int64_t defaultValue = 0);
uint64_t getULong64(const char* key, uint64_t defaultValue = 0);
float_t getFloat(const char* key, float_t defaultValue = NAN);
double_t getDouble(const char* key, double_t defaultValue = NAN);
bool getBool(const char* key, bool defaultValue = false);
size_t getString(const char* key, char* value, size_t maxLen);
String getString(const char* key, String defaultValue = String());
size_t getBytesLength(const char* key);
size_t getBytes(const char* key, void * buf, size_t maxLen);

size_t freeEntries();
```


