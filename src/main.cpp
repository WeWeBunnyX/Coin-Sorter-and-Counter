#include <Arduino.h>
#include <Wire.h>
#include <LCDI2C_Multilingual.h>

LCDI2C_Latin lcd(0x27, 16, 2);

const int sensorDigitalPins[] = {12, 11, 3, 8};
const int numSensors = 4;

volatile int count = 0; 
volatile unsigned long lastDetectionTime = 0;
const unsigned long debounceDelay = 40; // Increased debounce delay for better detection

volatile int totalPKR = 0; 
volatile int oddCount = 0; 

void countObject()
 {
  unsigned long currentTime = millis();
  if (currentTime - lastDetectionTime > debounceDelay) 
  {
    count++;
    lastDetectionTime = currentTime;
  }
}

void count5PKRCoin() {
  unsigned long currentTime = millis();
  if (currentTime - lastDetectionTime > debounceDelay) {
    totalPKR += 5;
    lastDetectionTime = currentTime;
  }
}

void count2PKRCoin() {
  unsigned long currentTime = millis();
  if (currentTime - lastDetectionTime > debounceDelay) {
    totalPKR += 2;
    lastDetectionTime = currentTime;
  }
}

void count10PKRCoin() {
  unsigned long currentTime = millis();
  if (currentTime - lastDetectionTime > debounceDelay) {
    totalPKR += 10;
    lastDetectionTime = currentTime;
  }
}

void countOddCoin() {
  unsigned long currentTime = millis();
  if (currentTime - lastDetectionTime > debounceDelay) {
    oddCount++;
    lastDetectionTime = currentTime;
  }
}

void initializeLCD()

 {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total PKR:");
 }

void initializeSensors() {
  for (int i = 0; i < numSensors; i++) 
  {
    pinMode(sensorDigitalPins[i], INPUT_PULLUP);
  }
  attachInterrupt(digitalPinToInterrupt(sensorDigitalPins[0]), count5PKRCoin, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensorDigitalPins[1]), count2PKRCoin, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensorDigitalPins[2]), count10PKRCoin, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensorDigitalPins[3]), countOddCoin, FALLING);
}

void updateLCD() 

{
  lcd.setCursor(6, 0);
  lcd.print("    ");
  lcd.setCursor(6, 0);
  lcd.print(totalPKR);
  lcd.setCursor(0, 1);
  lcd.print("Odd: ");
  lcd.print(oddCount);
}

void checkDigitalSensors() 

{
  for (int i = 0; i < numSensors; i++) 
  {
    int sensorDigitalValue = digitalRead(sensorDigitalPins[i]);
    if (sensorDigitalValue == LOW) 
    {
      switch (i) {
        case 0:
          count5PKRCoin();
          break;
        case 1:
          count2PKRCoin();
          break;
        case 2:
          count10PKRCoin();
          break;
        case 3:
          countOddCoin();
          break;
      }
    }
  }
}

void printSensorStates()
 {
  Serial.print("\r"); 

  for (int i = 0; i < numSensors; i++) 
  {
    int sensorDigitalValue = digitalRead(sensorDigitalPins[i]);
  
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(" - D: ");
    Serial.print(sensorDigitalValue);
    Serial.print(" | ");
  }
  Serial.print("Total PKR: ");
  Serial.print(totalPKR);
  Serial.print(" | Odd Count: ");
  Serial.print(oddCount);
  //delay(1); 
 }



void setup() 
{
  initializeLCD();
  Serial.begin(9600);
  initializeSensors();
}


void loop() 
{
  updateLCD();
  checkDigitalSensors();
  printSensorStates();
  // Removed delay for better response
}
