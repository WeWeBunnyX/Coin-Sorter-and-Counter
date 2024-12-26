#include <Arduino.h>
#define LED_PIN 13

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(LED_PIN, HIGH);
  delay(100); 

  digitalWrite(LED_PIN, LOW);
  delay(100); 
}
