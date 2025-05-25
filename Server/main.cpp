#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


constexpr uint8_t BT_RX    = 10;          // HC-05 → Nano
constexpr uint8_t BT_TX    = 11;          // Nano  → HC-05 
constexpr uint8_t BT_STATE = 2;           // HIGH while link is up
constexpr uint8_t LED_PIN  = LED_BUILTIN;


SoftwareSerial     BTSerial(BT_RX, BT_TX);
LiquidCrystal_I2C  lcd(0x27, 16, 2);      // change to 0x3F if your board needs it

bool   linked            = false;         // current link status
unsigned long splashEnds = 0;             

char   lineBuf[32];
uint8_t idx = 0;


float   lastT = NAN, lastH = NAN;
bool    haveValues = false;


void showSplash(const __FlashStringHelper* secondLine)
{
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print(F("BT ON"));
    lcd.setCursor(0, 1); lcd.print(secondLine);
}

void drawValues(float t, float h)
{
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print(F("T=")); lcd.print(t, 1); lcd.print(F("C"));
    lcd.setCursor(0, 1); lcd.print(F("H=")); lcd.print(h, 0); lcd.print(F("%"));
}


void setup()
{
    pinMode(BT_STATE, INPUT);
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(9600);
    BTSerial.begin(9600);          // slave, already configured in AT-mode

    lcd.init();
    lcd.backlight();
    showSplash(F("CONNECTING..."));
}


void loop()
{

    bool s = digitalRead(BT_STATE);

    if (s && !linked) {                           // link just came up
        Serial.println(F("[BT] senzor_1 connected"));
        linked      = true;
        splashEnds  = millis() + 5000UL;          // "loading screen"
        showSplash(F("CONNECTED"));
    }
    if (!s && linked) {                           // link lost
        Serial.println(F("[BT] senzor_1 disconnected"));
        linked       = false;
        haveValues   = false;
        showSplash(F("CONNECTING..."));
    }
    digitalWrite(LED_PIN, s);

    
    while (BTSerial.available()) {
        char c = BTSerial.read();

        if (c == '\n' || c == '\r') {             // end of line
            if (idx) {
                lineBuf[idx] = '\0';
                float t = atof(strtok(lineBuf, ","));      // temp
                float h = atof(strtok(nullptr , ","));     // humidity

                lastT = t; lastH = h; haveValues = true;

                Serial.print(F("T=")); Serial.print(t);
                Serial.print(F("  H=")); Serial.println(h);

                
                if (millis() > splashEnds) drawValues(t, h);
                idx = 0;
            }
        } else if (idx < sizeof(lineBuf) - 1) {
            lineBuf[idx++] = c;
        }
    }

    
    if (splashEnds && millis() > splashEnds) {
        splashEnds = 0;            
        if (haveValues) drawValues(lastT, lastH);
    }

    /* optional USB→BT passthrough */
    if (Serial.available()) BTSerial.write(Serial.read());
}
