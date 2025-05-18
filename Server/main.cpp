#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

constexpr uint8_t BT_RX    = 10;          // HC-05 TXD -> Nano
constexpr uint8_t BT_TX    = 11;          // HC-05 RXD <- Nano
constexpr uint8_t BT_STATE = 2;           // HIGH when linked
constexpr uint8_t LED_PIN  = LED_BUILTIN; // onboard LED

SoftwareSerial BTSerial(BT_RX, BT_TX);
LiquidCrystal_I2C lcd(0x27, 16, 2);       // use 0x3F if 0x27 fails

bool lastState = false;

void setup() {
    pinMode(BT_STATE, INPUT);
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(9600);
    BTSerial.begin(9600);

    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ai pierdut");
    lcd.setCursor(0, 1);
    lcd.print("Jocul.");

    Serial.println(F("System up…"));
    Serial.println(F("Bluetooth module online, waiting for connection."));
}

void loop() {
    bool state = digitalRead(BT_STATE);
    if (state && !lastState)        Serial.println(F(">> Bluetooth device connected"));
    else if (!state && lastState)   Serial.println(F(">> Bluetooth device disconnected"));
    lastState = state;
    digitalWrite(LED_PIN, state);

    if (BTSerial.available())  Serial.write(BTSerial.read());
    if (Serial.available())    BTSerial.write(Serial.read());
}
