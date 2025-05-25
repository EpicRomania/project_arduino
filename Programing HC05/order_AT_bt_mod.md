# HC-05 Bluetooth Module Wiring to Arduino Nano

## Wiring

> **Note:** The first two lines establish the serial communication between the HC-05 and the Nano.
> TXD (Transmit) of the HC-05 connects to RX (Receive) of the Nano, and RXD connects to TX. This allows the two devices to exchange data properly.

> **KEY Pin Info:** The `EN` pin is connected to 5V **only when you want to enter AT command mode**. It should be set **high** before powering the module to trigger AT mode.

> **RX0->RXD WITHOUT ANY RESISTORS**

### Wiring Table


| HC-05 Pin | Arduino Nano Pin | Description                   |
|-----------|------------------|-------------------------------|
| RXD       | rX0 (D0)         | Serial receive (from Nano TX) |
| TXD       | TX1 (D1)         | Serial transmit (to Nano RX)  |
| GND       | GND              | Ground                        |
| VCC       | 5V               | Power supply                  |
| EN        | 5V               | Enable AT mode (optional use) |

> **HC-05 RXD Voltage Divider:**  
> To protect the module’s RXD pin, you’ve inserted a simple divider on the line into D11:  
> - HC-05 RXD -> 1 kΩ -> D11  
> - D11 -> 1 kΩ -> GND  

---

## AT Commands for Configuration

Once the HC-05 module is wired correctly and powered with the `EN` (KEY) pin high, you can enter AT command mode to configure its settings.

- Connect to **COM3** (or your detected COM port) using a serial monitor.
- Baud rate: **38400**.
- Line ending: **Both NL & CR**.
- **Important:** Each character you type is immediately sent over serial-**you must type each letter manually**. You **cannot** paste or edit commands after starting to type.

### Module LED Behavior:

- When the HC-05 is in **AT command mode**, the onboard LED will **blink slowly at ~0.5 Hz** (1 blink every 2 seconds).
- After sending `AT+RESET`, the LED will **flash rapidly**, indicating a reboot.

Use the following commands to set the module name, define its role, set the pairing password, and apply changes:

```commands_in_order
AT
AT+NAME=server/senzor_n
AT+ROLE=0/1 (slave-server / master-senzor_n)
AT+PSWD=1234
AT+RESET
```
### Device off Pictures

![Photo 1](/Programing%20HC05/Photos/1.jpg) 
![Photo 2](/Programing%20HC05/Photos/2.jpg) 
![Photo 3](/Programing%20HC05/Photos/3.jpg)

### Device on Pictures

![Photo 4](/Programing%20HC05/Photos/4.jpg)
![Photo 5](/Programing%20HC05/Photos/5.jpg)