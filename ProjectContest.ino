#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  dataDisplay();
  waterPump(0);
  delay(200);  
  waterPump(1);
  delay(500);  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  lcd.clear();
  while(moistureRead() > 0 && moistureRead() <= 3){
    lcd.setCursor(0,0);
    lcd.print("Moisture: ");
    lcd.setCursor(0,10);
    lcd.print(moistureRead());
    lcd.setCursor(0,1);
    lcd.print("PUMPING");
    waterPump(0);
    delay(1000);
    if(moistureRead() > 3){
      waterPump(1);
      break;
    }
  } 
  
  lcd.clear();
  while(moistureRead() >= 4 && moistureRead() <= 7){
    lcd.setCursor(0,0);
    lcd.print("Moisture: ");
    lcd.setCursor(0,10);
    lcd.print(moistureRead());
    lcd.setCursor(0,1);
    lcd.print("NEEDS WATER...");    
  } 
  
  lcd.clear();
  while(moistureRead() >= 8 && moistureRead() <= 10){
    lcd.setCursor(0,0);
    lcd.print("Moisture: ");
    
    
       
    if(moistureRead() == 10){
      lcd.setCursor(10,0);
      lcd.print("  ");
      lcd.setCursor(10,0);
      lcd.print(moistureRead());;
    } else{
      lcd.setCursor(10,0);
      lcd.print("   ");
      lcd.setCursor(10,0);
      lcd.print(moistureRead());
    }
    lcd.setCursor(0,1);
    lcd.print("WELL-WATERED");
        
  }   
}

void waterPump(int stat){
  digitalWrite(7, stat);
}

int moistureRead(){
  int val = analogRead(A8);
  int value = map(val,220,1023,10,1);
  delay(1000);
  return value;
}

void dataDisplay(){
  lcd.setCursor(0,0);
  lcd.print("CRU EP & MEP");
  lcd.setCursor(0,1);
  lcd.print("Open House 2023");
  delay(5000);  
}