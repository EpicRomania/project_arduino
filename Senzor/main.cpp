#include <Arduino.h>
#include <SoftwareSerial.h>

#include <DHT.h>

constexpr uint8_t BT_RX     = 10;            // Arduino D10 <- HC-05 TXD
constexpr uint8_t BT_TX     = 11;            // Arduino D11 -> HC-05 RXD
constexpr uint8_t BT_STATE  = 2;             // HIGH when connected
constexpr uint8_t LED_PIN   = LED_BUILTIN;   // onboard LED

#define DHTPIN 4              // D4 wired above
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

unsigned long lastRead = 0;

SoftwareSerial BTSerial(BT_RX, BT_TX);       // RX, TX
bool lastState = false;

void setup() {
    pinMode(BT_STATE, INPUT);
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(9600);
    BTSerial.begin(9600);

    Serial.println(F("System up…"));
    Serial.println(F("Bluetooth module online, waiting for connection."));
    dht.begin();
        Serial.println(F("DHT22 module online, waiting for connection."));
}

void loop() {
    bool state = digitalRead(BT_STATE);

    if (state && !lastState)        Serial.println(F(">> Bluetooth device connected"));
    else if (!state && lastState)   Serial.println(F(">> Bluetooth device disconnected"));

    lastState = state;
    digitalWrite(LED_PIN, state);   // LED on while linked

    if (BTSerial.available())  Serial.write(BTSerial.read());
    if (Serial.available())    BTSerial.write(Serial.read());

    if (millis() - lastRead >= 2000) {        // DHT min-period ~2 s
        lastRead = millis();

        float t = dht.readTemperature();      // °C
        float h = dht.readHumidity();         // %

        if (isnan(t) || isnan(h)) {
            Serial.println(F("DHT read failed"));
        } else {
            Serial.print(F("Temp: ")); Serial.print(t); Serial.print(F(" °C  "));
            Serial.print(F("Hum: "));  Serial.print(h); Serial.println(F(" %"));

          
           
        }
    }
}






