> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/guia-de-programacion-del-esp32-en-entorno-arduino/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## Designación de los pines
```cpp
digitalWrite(14, LOW);  // GPIO14
```


## Salidas y entradas digitales (GPIO)
```cpp
pinMode(pin, mode)
```

```cpp
digitalWrite(pin, output)
```

```cpp
digitalRead(pin)
```


## Entradas analógicas (ADC)
```cpp
analogRead(A0)
```


## Interrupciones
```cpp
attachInterrupt(digitalPinToInterrupt(interruptPin), handler, FALLING);
```


## PROGMEM
```cpp
string text1 = F("hello");
string text2 = F("hello");
```

```cpp
const char hello[] PROGMEM = "hello";
string texto1 = FSPTR(hello);
string texto2 = FSPTR(hello);
```


