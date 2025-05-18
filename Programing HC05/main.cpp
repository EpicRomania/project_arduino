#include <Arduino.h>

void setup() {
  Serial.begin(38400);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    Serial.write(c);  // echoes back so you can see it in the monitor
  }
}
