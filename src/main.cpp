#include <Arduino.h>
#include <Wire.h>
#include <LCDI2C_Multilingual.h>

LCDI2C_Latin lcd(0x27, 16, 2);

const int sensorDigitalPins[] = {12, 11, 3, 8};
const int numSensors = 4;

volatile int count = 0; 
volatile unsigned long lastDetectionTime = 0;
const unsigned long debounceDelay = 50; // Increased debounce delay for better detection

void countObject() {
  unsigned long currentTime = millis();
  // Only register if debounce time has passed
  if (currentTime - lastDetectionTime > debounceDelay) {
    count++;
    lastDetectionTime = currentTime;
  }
}

void initializeLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Count:");
}

void initializeSensors() {
  for (int i = 0; i < numSensors; i++) {
    pinMode(sensorDigitalPins[i], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(sensorDigitalPins[i]), countObject, FALLING); // Trigger on falling edge
  }
}

void updateLCD() {
  lcd.setCursor(6, 0);
  lcd.print("    ");
  lcd.setCursor(6, 0);
  lcd.print(count);
}

void checkDigitalSensors() {
  for (int i = 0; i < numSensors; i++) {
    int sensorDigitalValue = digitalRead(sensorDigitalPins[i]);
    if (sensorDigitalValue == LOW) {
      countObject();
    }
  }
}

void printSensorStates() {
  Serial.print("\r"); 
  for (int i = 0; i < numSensors; i++) {
    int sensorDigitalValue = digitalRead(sensorDigitalPins[i]);
  
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(" - D: ");
    Serial.print(sensorDigitalValue);
    Serial.print(" | ");
  }
  Serial.print("Count: ");
  Serial.print(count);
  //delay(1); 
}

void setup() {
  initializeLCD();
  Serial.begin(9600);
  initializeSensors();
}

void loop() {
  updateLCD();
  checkDigitalSensors();
  printSensorStates();
  // Removed delay for better response
}
