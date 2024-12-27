#include <Arduino.h>
#include <Wire.h>
#include <LCDI2C_Multilingual.h>

LCDI2C_Latin lcd(0x27, 16, 2);

const int sensor1DigitalPin = 12;
const int sensor1AnalogPin = A0;

const int sensor2DigitalPin = 11;
const int sensor2AnalogPin = A1;

const int sensor3DigitalPin = 3;
const int sensor3AnalogPin = A2;

const int sensor4DigitalPin = 8;
const int sensor4AnalogPin = A3;

void setup() {
  lcd.init();      
  lcd.backlight();  

  lcd.clear();   
  lcd.setCursor(0, 0);  
  lcd.print("12345");   

  Serial.begin(9600);

  pinMode(sensor1DigitalPin, INPUT);
  pinMode(sensor1AnalogPin, INPUT);

  pinMode(sensor2DigitalPin, INPUT);
  pinMode(sensor2AnalogPin, INPUT);

  pinMode(sensor3DigitalPin, INPUT);
  pinMode(sensor3AnalogPin, INPUT);

  pinMode(sensor4DigitalPin, INPUT);
  pinMode(sensor4AnalogPin, INPUT);
}

void loop() {
  // Read sensor values
  int sensor1DigitalValue = digitalRead(sensor1DigitalPin);
  int sensor1AnalogValue = analogRead(sensor1AnalogPin);

  int sensor2DigitalValue = digitalRead(sensor2DigitalPin);
  int sensor2AnalogValue = analogRead(sensor2AnalogPin);

  int sensor3DigitalValue = digitalRead(sensor3DigitalPin);
  int sensor3AnalogValue = analogRead(sensor3AnalogPin);

  int sensor4DigitalValue = digitalRead(sensor4DigitalPin);
  int sensor4AnalogValue = analogRead(sensor4AnalogPin);

 
  Serial.print("Sensor 1 - D: ");
  Serial.print(sensor1DigitalValue);
  Serial.print(", A: ");
  Serial.print(sensor1AnalogValue);
  Serial.print(" | Sensor 2 - D: ");
  Serial.print(sensor2DigitalValue);
  Serial.print(", A: ");
  Serial.print(sensor2AnalogValue);
  Serial.print(" | Sensor 3 - D: ");
  Serial.print(sensor3DigitalValue);
  Serial.print(", A: ");
  Serial.print(sensor3AnalogValue);
  Serial.print(" | Sensor 4 - D: ");
  Serial.print(sensor4DigitalValue);
  Serial.print(", A: ");
  Serial.print(sensor4AnalogValue);
  Serial.print("\r");  

  delay(1000);  
}


