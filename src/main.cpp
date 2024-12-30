#include <Arduino.h>
#include <Wire.h>
#include <LCDI2C_Multilingual.h>

LCDI2C_Latin lcd(0x27, 16, 2);

const int sensorDigitalPins[] = {12, 11, 3, 8};
const int sensorAnalogPins[] = {A0, A1, A2, A3};
const int numSensors = 4;

volatile int count = 0; 
volatile unsigned long lastDetectionTime = 0;
const unsigned long debounceDelay = 0.5; // Reduced debounce delay for faster detection

void countObject() {
  unsigned long currentTime = millis();
  if (currentTime - lastDetectionTime > debounceDelay) {
    count++;
    lastDetectionTime = currentTime;
    Serial.print("Count: ");
    Serial.println(count);
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
    attachInterrupt(digitalPinToInterrupt(sensorDigitalPins[i]), countObject, FALLING);
  }
}

void updateLCD() {
  lcd.setCursor(6, 0);
  lcd.print("    ");
  lcd.setCursor(6, 0);
  lcd.print(count);
}

void checkAnalogSensors() {
  int sensor1AnalogValue = analogRead(sensorAnalogPins[0]);          // Sensor 1 
  if (sensor1AnalogValue < 610) {
    count++;
    updateLCD();
    delay(10); // Small delay to avoid multiple increments for the same detection
  }

  int sensor2AnalogValue = analogRead(sensorAnalogPins[1]);            //Sensor 2
  if (sensor2AnalogValue < 580) {
    count++;
    updateLCD();
    delay(10); // Small delay to avoid multiple increments for the same detection
  }
}

void printSensorStates() {
  Serial.print("\r"); 
  for (int i = 0; i < numSensors; i++) {
    int sensorDigitalValue = digitalRead(sensorDigitalPins[i]);
    int sensorAnalogValue = analogRead(sensorAnalogPins[i]);
  
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(" - D: ");
    Serial.print(sensorDigitalValue);
    Serial.print(", A: ");
    Serial.print(sensorAnalogValue);
    Serial.print(" | ");
  }
  Serial.print("Count: ");
  Serial.print(count);
}

void setup() {
  initializeLCD();
  Serial.begin(9600);
  initializeSensors();
}

void loop() {
  updateLCD();
  checkAnalogSensors();
  printSensorStates();
  delay(1); // Small delay for display updates
}
