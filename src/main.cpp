#include <Arduino.h>
#include <Wire.h>
#include <LCDI2C_Multilingual.h>

LCDI2C_Latin lcd(0x27, 16, 2);  

void setup() {
  lcd.init();       
  lcd.backlight();   
  
  lcd.command(0x0C);  

  lcd.clear();  
}

void loop() {
  for (int i = 1; i <= 100; i++) {
    lcd.clear();   
    lcd.setCursor(0, 0);   
    lcd.print(i);   

    delay(500);  
  }
}
