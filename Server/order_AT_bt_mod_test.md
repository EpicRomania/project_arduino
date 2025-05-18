# Arduino Nano: HC-05 Bluetooth Module + LCD 1602 I2C Display

### Wiring:

> **Note:**
> - **D10/D11** are general-purpose digital I/O pins (not hardware UART) and work reliably with `SoftwareSerial`.  
> - **D2** reads the HC-05 `STATE` pin (goes HIGH when paired).  
> - The HC-05 `EN` (KEY) pin is **not** used here (AT mode only).  
> - The LCD uses I2C: **SDA** -> A4, **SCL** -> A5.

## Wiring Table

| Device      | Module Pin | Arduino Nano Pin | Description                          |
|-------------|------------|------------------|--------------------------------------|
| **HC-05**   | RXD        | D11              | `SoftwareSerial` RX (from Nano TX)   |
|             | TXD        | D10              | `SoftwareSerial` TX (to Nano RX)     |
|             | STATE      | D2               | Connection status (HIGH when paired) |
|             | VCC        | 5V               | Power (4-6 V DC)                     |
|             | GND        | GND              | Ground                               |
| **LCD I2C** | VCC        | 5V               | Power (4.5-5.5 V)                    |
|             | GND        | GND              | Ground                               |
|             | SDA        | A4               | I2C data                             |
|             | SCL        | A5               | I2C clock                            |

> **HC-05 RXD Voltage Divider:**  
> - HC-05 RXD -> 1 kΩ -> D11  
> - D11 -> 1 kΩ -> GND  

---

This 16×2 yellow-green backlit LCD (HD44780) is designed for low-power applications at 5 V.

**LCD 1602 I2C Specs**  
- Input voltage: 4.5-5.5 V  
- Supply current: 1.5 mA  
- Backlight current: 120 mA (4.1-4.3 V)

**Usage Instructions:**  
1. Connect the LCD to the Nano as shown above.  
2. In `platformio.ini`, add:
```ini
   lib_deps =
       587  ; LiquidCrystal I2C
```
2. In `main.cpp`, add:
```cpp
    #include <LiquidCrystal_I2C.h>
        ///
    void setup() {
        ///
    lcd.init();
    lcd.backlight();
    lcd.clear();
        ///
    }
```


![Photo 1](/Server/Photos/1.jpg)
![Photo 2](/Server/Photos/2.jpg)
![Photo 3](/Server/Photos/3.jpg)
![Photo 4](/Server/Photos/4.jpg) 
![Photo 5](/Server/Photos/5.jpg)


