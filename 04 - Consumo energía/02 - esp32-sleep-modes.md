> Códigos de ejemplo de los tutoriales de www.luisllamas.es
>
> Enlace entrada: https://www.luisllamas.es/esp32-sleep-modes/
>
> Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa

## WakeUp Sources
```cpp
// Light Sleep y Deep Sleep
esp_err_t esp_sleep_enable_timer_wakeup(uint64_t time_in_us);
esp_err_t esp_sleep_enable_touchpad_wakeup(void);
esp_err_t esp_sleep_enable_ulp_wakeup(void);
esp_err_t esp_sleep_enable_ext0_wakeup(gpio_num_t gpio_num, int level);
esp_err_t esp_sleep_enable_ext1_wakeup(uint64_t mask, esp_sleep_ext1_wakeup_mode_t mode);

// Solo en light Sleep
esp_err_t esp_sleep_enable_gpio_wakeup(void);
esp_err_t esp_sleep_enable_uart_wakeup(int uart_num);
esp_err_t esp_sleep_enable_wifi_wakeup(void);
void esp_sleep_enable_gpio_switch(bool enable);
```

```cpp
esp_err_t esp_sleep_pd_config(esp_sleep_pd_domain_t domain,
                                   esp_sleep_pd_option_t option);
```

```cpp
/**
 * @brief Power domains which can be powered down in sleep mode
 */
typedef enum {
    ESP_PD_DOMAIN_RTC_PERIPH,      //!< RTC IO, sensors and ULP co-processor
    ESP_PD_DOMAIN_RTC_SLOW_MEM,    //!< RTC slow memory
    ESP_PD_DOMAIN_RTC_FAST_MEM,    //!< RTC fast memory
    ESP_PD_DOMAIN_XTAL,            //!< XTAL oscillator
#if SOC_PM_SUPPORT_CPU_PD
    ESP_PD_DOMAIN_CPU,             //!< CPU core
#endif
    ESP_PD_DOMAIN_RTC8M,           //!< Internal 8M oscillator
    ESP_PD_DOMAIN_VDDSDIO,         //!< VDD_SDIO
    ESP_PD_DOMAIN_MAX              //!< Number of domains
} esp_sleep_pd_domain_t;
```

```cpp
/**
 * @brief Power down options
 */
typedef enum {
    ESP_PD_OPTION_OFF,      //!< Power down the power domain in sleep mode
    ESP_PD_OPTION_ON,       //!< Keep power domain enabled during sleep mode
    ESP_PD_OPTION_AUTO      //!< Keep power domain enabled in sleep mode, if it is needed by one of the wakeup options. Otherwise power it down.
} esp_sleep_pd_option_t;
```


## Disable Sleep Wakeup Source
```cpp
/**
 * @brief Disable wakeup source
 *
 * This function is used to deactivate wake up trigger for source
 * defined as parameter of the function.
 * @param source - number of source to disable of type esp_sleep_source_t
 */
esp_err_t esp_sleep_disable_wakeup_source(esp_sleep_source_t source);
```


## Obtener WakeUp Cause
```cpp
/**
 * @brief Sleep wakeup cause
 */
typedef enum {
    ESP_SLEEP_WAKEUP_UNDEFINED,    //!< In case of deep sleep, reset was not caused by exit from deep sleep
    ESP_SLEEP_WAKEUP_ALL,          //!< Not a wakeup cause, used to disable all wakeup sources with esp_sleep_disable_wakeup_source
    ESP_SLEEP_WAKEUP_EXT0,         //!< Wakeup caused by external signal using RTC_IO
    ESP_SLEEP_WAKEUP_EXT1,         //!< Wakeup caused by external signal using RTC_CNTL
    ESP_SLEEP_WAKEUP_TIMER,        //!< Wakeup caused by timer
    ESP_SLEEP_WAKEUP_TOUCHPAD,     //!< Wakeup caused by touchpad
    ESP_SLEEP_WAKEUP_ULP,          //!< Wakeup caused by ULP program
    ESP_SLEEP_WAKEUP_GPIO,         //!< Wakeup caused by GPIO (light sleep only)
    ESP_SLEEP_WAKEUP_UART,         //!< Wakeup caused by UART (light sleep only)
    ESP_SLEEP_WAKEUP_WIFI,              //!< Wakeup caused by WIFI (light sleep only)
    ESP_SLEEP_WAKEUP_COCPU,             //!< Wakeup caused by COCPU int
    ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG,   //!< Wakeup caused by COCPU crash
    ESP_SLEEP_WAKEUP_BT,           //!< Wakeup caused by BT (light sleep only)
} esp_sleep_source_t;
```

```cpp
void print_wakeup_touchpad(){
  touchPin = esp_sleep_get_touchpad_wakeup_status();
  Serial.printf("Touch detectado en d\n",touchPin);
}
```

```cpp
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();
  Serial.printf("Touch detectado en d\n",wakeup_reason);
}
```

```cpp
void print_wakeup_ext1(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_ext1 = esp_sleep_get_wakeup_cause();
  Serial.printf("Ext1 en d\n", wakeup_ext1);
}
```


## Desactivar radio
```cpp
esp_bluedroid_disable()
esp_bt_controller_disable()
esp_wifi_stop()
```

```cpp
btStop();
WiFi.mode(WIFI_OFF);
```


