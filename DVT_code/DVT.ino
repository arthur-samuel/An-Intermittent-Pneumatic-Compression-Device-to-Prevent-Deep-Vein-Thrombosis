#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("WELCOME");
  delay(4000);
  lcd.setCursor(5,0);
  lcd.print("DVT Device");
  delay(4000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("FESTUS ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("HAWA ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("and NATANIEL");
  delay(4000); 
  lcd.clear();

}  



void loop() {
  
}
