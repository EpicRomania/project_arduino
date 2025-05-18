# Arduino Nano: HC-05 Bluetooth Module + DHT22 Sensor

### Wiring:

> **Note:**
>
> - **D10/D11** are general-purpose digital I/O port pins (not hardware UART) and are the only ones that work reliably with `SoftwareSerial`.
> - **D2** reads the HC-05 `STATE` pin (goes HIGH when paired).
> - The HC-05 `EN` (KEY) pin is **not** used here, it’s only needed to enter AT mode on power-up.
> - **D4** reads the DHT22’s digital data line (built-in pull-up resistor).

## Wiring Table


| Device    | Module Pin | Arduino Nano Pin | Description                                 |
|-----------|------------|------------------|---------------------------------------------|
| **HC-05** | RXD        | D11              | `SoftwareSerial` RX (from Nano TX)          |
|           | TXD        | D10              | `SoftwareSerial` TX (to Nano RX)            |
|           | STATE      | D2               | Connection status output (HIGH when paired) |
|           | VCC        | 5V               | Power (4-6 V DC)                            |
|           | GND        | GND              | Ground                                      |
| **DHT22** | +          | 5V or 3.3V       | Power (3.3-6 V DC)                          |
|           | OUT        | D4               | Data (digital, built-in pull-up)            |
|           | –          | GND              | Ground                                      |

> **HC-05 RXD Voltage Divider:**  
> To protect the module’s RXD pin, you’ve inserted a simple divider on the line into D11:  
> - HC-05 RXD -> 1 kΩ -> D11  
> - D11 -> 1 kΩ -> GND  

---

## DHT22 Ranges & PlatformIO Setup

- **Operating voltage:** 3.3 - 6 V DC
- **Temperature range:** -40 °C to +80 °C (+- 0.5 °C)
- **Humidity range:** 0 - 100 % RH
- **Read interval:** >= 2 s

1.In `platformio.ini`, add your sensor libraries:
```ini
    lib_deps =
        19    ; DHT sensor library
        31    ; Adafruit Unified Sensor
```

2.In 'main.cpp', add:
```cpp
    #include <DHT.h>
```