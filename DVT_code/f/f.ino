#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX710B.h>

int DOUT = 8; // Pressure sensor data pin
int SCLK = 9; // Pressure sensor clock pin
int PUMP_PIN = 4; // Pin for MOSFET connected to pneumatic pump
int VALVE_PIN = 5; // Pin for transistor conne\cted to solenoid valve

HX710B pressure_sensor(DOUT, SCLK); // Initialize HX710B with DOUT and SCLK pins
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(57600);

  pinMode(PUMP_PIN, OUTPUT);
  pinMode(VALVE_PIN, OUTPUT);

  lcd.begin(); 
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("IPC DEVICE");
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
  lcd.print("and NATHANIEL");
  delay(2000); 
  lcd.clear();

}

void loop() {
  int sensTime = 0; // This records the number of inflation phases that have occurred
  int sensValue =0;
  while (sensTime <= 10) {
    // Inflation Phase
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Inflation Phase");
    delay(2000);
    //sensValue = pressure_sensor.mmHg();

    digitalWrite(VALVE_PIN, HIGH); // Close the solenoid valve during inflation
    digitalWrite(PUMP_PIN, HIGH); // Activate the pneumatic pump

    
    do {
      int sensValue = 0;
      sensValue = analogRead(A0); // Assuming 'read' is the method to get the pressure reading
      Serial.println(sensValue); // For debugging

      if (sensValue >= 5 && sensValue < 7) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Inflation Phase");
        lcd.setCursor(0, 1);
        lcd.print("Pressure: ");
        lcd.print(sensValue);
        lcd.print(" mmHg");
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Air pressure low");
        lcd.setCursor(0, 1);
        lcd.print(sensValue);
        lcd.print(" mmHg");
      }
    } while (sensValue < 7);

    delay(40000); // Wait for 40 seconds at target pressure

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pressure: OK");
    delay(3000);

    // Deflation Phase
    digitalWrite(VALVE_PIN, LOW); // Open the solenoid valve to release air
    digitalWrite(PUMP_PIN, LOW); // Turn off the pneumatic pump

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Deflation Phase");
    lcd.setCursor(4, 1);
    lcd.print("Relax ^-^");
    delay(50000); // Wait for 50 seconds during deflation phase

    sensTime += 1; // Increment the phase counter
  }

  delay(50000); // Wait for 50 seconds before restarting the loop
}
