#include <Wire.h>
#include <Arduino.h>
#include <LCDI2C_Multilingual.h>

LCDI2C_Generic lcd(0x27, 16, 2); 

void setup() {
  lcd.init();        
  lcd.backlight();  
  
  lcd.command(0x0C);  

  lcd.clear();   

  lcd.setCursor(0, 0);  
  lcd.print("Hello, World!");
  
  lcd.setCursor(0, 1);   
  lcd.print("I2C LCD Test");
}

void loop() {
 
}

