/*
 * Arduino Air Quality Monitor
 * 
 * learnelectronics
 * 24 MAR 2017
 * 
 * www.youtube.com/c/learnelectronics
 * arduino0169@gmail.com
 * 
 * 
 * Be sure to burn in sensor by leaving
 * plugged in for 24 hours before initial
 * use, then calibrate by placing outside
 * for at least 10 minutes. Outdoor C02
 * levels are between 380-400ppm unless
 * you live in Shenzen. If you live in
 * this ain't gonna help you.
 */



#include <LiquidCrystal.h>                //LCD Library


#define beeper    8                       //beeper on Digital 8
#define sensor    A0                      //sensor on Analog 0



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    //Create instance of LCD

int gasLevel = 0;                         //int variable for gas level
String quality ="";
String gasvalue ="";

void setup() {
  Serial.begin(9600);                     //start serial comms
  pinMode(beeper,OUTPUT);                 //set beeper for output
  pinMode(sensor,INPUT);                  //set sensor for input

  
  lcd.begin(16, 2);                       //initial LCD setup
  lcd.setCursor (0,0);                    //splash screen and warmup
  
   lcd.print("   SHAPERJET    ");
   delay(3000);
   lcd.setCursor (0,0);                    //splash screen and warmup
  lcd.print("                ");
  lcd.setCursor (0,1);
  lcd.print("                ");
  lcd.setCursor (0,0);
  lcd.print("   Air Sensor   ");
  lcd.setCursor (0,1);
  lcd.print("   Warming Up   ");
  delay(2000);                            //set for at least 2 minutes

  lcd.setCursor (0,0);                    //clear screen
  lcd.print("                ");
  lcd.setCursor (0,1);
  lcd.print("                ");
  
}

void loop() {
  gasLevel = analogRead(sensor);

  if(gasLevel<100){
    quality = "Fresh Air!      ";
    digitalWrite(8, LOW);

  lcd.setCursor (0,0);
lcd.print("Air Quality is:");
lcd.setCursor(0,1);
lcd.print(quality);
lcd.setCursor(11,1);
gasLevel = map(gasLevel, 0, 1023, 10, 100);
gasvalue = String(gasLevel);
lcd.print(gasvalue);
lcd.print("%");
  
  
  
  }
  else if (gasLevel >100 && gasLevel<250){
    quality = "Moderate        ";
    digitalWrite(8, LOW);
  
  lcd.setCursor (0,0);
lcd.print("Air Quality is:");
lcd.setCursor(0,1);
lcd.print(quality);
lcd.setCursor(11,1);
gasLevel = map(gasLevel, 0, 1023, 25, 100);
gasvalue = String(gasLevel);
lcd.print(gasvalue);
lcd.print("%");
  
  
  }
  else if (gasLevel >250 && gasLevel<400){
    quality = "Poor Air        ";
    digitalWrite(8, LOW);
  
  lcd.setCursor (0,0);
lcd.print("Air Quality is:");
lcd.setCursor(0,1);
lcd.print(quality);
lcd.setCursor(11,1);
gasLevel = map(gasLevel, 0, 1023, 40, 100);
gasvalue = String(gasLevel);
lcd.print(gasvalue);
lcd.print("%");
  
  
  }
  else if (gasLevel >400){
    quality = "Danger!!!!!!!   ";
    digitalWrite(8, HIGH);
  
  lcd.setCursor (0,0);
lcd.print("Air Quality is:");
lcd.setCursor(0,1);
lcd.print(quality);
lcd.setCursor(11,1);
gasLevel = map(gasLevel, 0, 1023, 65, 100);
gasvalue = String(gasLevel);
lcd.print(gasvalue);
lcd.print("%");
  
  
  }

delay(500);
}
/*
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 5K pot:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

*/



