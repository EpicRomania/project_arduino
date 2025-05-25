#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DHT.h>

constexpr uint8_t BT_RX     = 10;   // HC-05 TXD → Nano
constexpr uint8_t BT_TX     = 11;   // Nano  TXD → HC-05 RXD (via divider)
constexpr uint8_t BT_STATE  = 2;
constexpr uint8_t DHT_PIN   = 4;
constexpr uint8_t LED_PIN   = LED_BUILTIN;

SoftwareSerial BTSerial(BT_RX, BT_TX);
DHT            dht(DHT_PIN, DHT22);

bool linked = false;
unsigned long lastSend = 0;

void setup()
{
    pinMode(BT_STATE, INPUT);
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(9600);
    BTSerial.begin(9600);     // master auto-connects (CMODE=1)
    dht.begin();
}

void loop()
{
    bool s = digitalRead(BT_STATE);

    if (s && !linked)  { Serial.println(F("[BT] link up"));   linked = true; }
    if (!s && linked)  { Serial.println(F("[BT] link down")); linked = false; }
    digitalWrite(LED_PIN, s);

    if (linked && millis() - lastSend >= 2000UL) {
        lastSend = millis();
        float t = dht.readTemperature();
        float h = dht.readHumidity();
        if (!isnan(t) && !isnan(h)) {
            BTSerial.print(t, 1);
            BTSerial.print(',');
            BTSerial.println(h, 0);
        } else {
            Serial.println(F("[DHT] read error"));
        }
    }

    if (BTSerial.available()) Serial.write(BTSerial.read());
}
