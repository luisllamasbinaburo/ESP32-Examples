> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-adc/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Cómo leer la entrada analógica del ESP32
```cpp
void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(100);
}
```


## Más funciones útiles
```cpp
// Establece los bits de muestra y la resolución.
// Puede ser un valor entre 9 (0 – 511) a 12 bits (0 – 4095).
// Resolución predeterminada: 12 bits.
analogReadResolution(resolución);

// Establece los bits de muestra y la resolución.
// Puede ser un valor entre 9 (0 – 511) y 12 bits (0 – 4095).
// Resolución predeterminada: 12 bits.
analogSetWidth(ancho);

// Establece el número de ciclos por muestra.
// Valor predeterminado: 8. Rango: 1 a 255.
analogSetCycles(ciclos);

// Establece el número de muestras en el rango.
// Tiene un efecto de aumentar la sensibilidad.
// Valor predeterminado: 1 muestra.
analogSetSamples(muestras);

// Establece el divisor para el reloj del ADC.
// Valor predeterminado: 1. Rango: 1 a 255.
analogSetClockDiv(attenuation);

// Establece la atenuación de entrada para todos los pines ADC.
// Valor predeterminado: ADC\_11db.
// Valores aceptados:
// - ADC\_0db: sin atenuación
// - ADC\_2\_5db: atenuación extendidamV.
// - ADC\_6db: atenuación extendida
// - ADC\_11db: atenuación extendida
analogSetAttenuation(atenuación);

// Establece la atenuación de entrada para el pin especificado.
// Valor predeterminado: ADC\_11db.
// Valores de atenuación iguales a la función anterior.
analogSetPinAttenuation(pin, atenuación);

// Asocia un pin al ADC (también despeja cualquier otro modo analógico que pueda estar activo).
// Devuelve un resultado VERDADERO o FALSO.
adcAttachPin(pin);

// Inicia una conversión ADC en el bus del pin asociado.
// Verifica si la conversión en el bus ADC del pin está en curso actualmente.
// Devuelve VERDADERO o FALSO.
// Obtiene el resultado de la conversión: devuelve un entero de 16 bits.
adcStart(pin);
adcBusy(pin);
adcEnd(pin);
```


