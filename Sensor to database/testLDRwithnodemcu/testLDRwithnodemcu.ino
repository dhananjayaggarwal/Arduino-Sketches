#include <ESP8266WiFi.h>

unsigned long interval = 30000;
String ldrvalue;

const int analog_ip = A0; //Naming analog input pin
int inputVal  = 0;        //Variable to store analog input values

void setup() {
  Serial.begin(9600);
  delay(10);
  

}

void ldrRead();


void MinuteDelay(int number){
  for (int i = 0; i < number; ++i)
    {
      
      // use 6 10 second delays for each minute // with a yield before each
      for(int j=0; j<6 ;j++)
      {
        Serial.print("*");
        // yield();
        delay(10000);
        
      }
    }
  }

void loop() {
  
 
  

ldrRead();
delay(1000);

MinuteDelay(5);    
   


   
    
 
}


void ldrRead()
{
  
  inputVal = analogRead (analog_ip); // Analog Values 0 to 1023

  inputVal = map(inputVal, 0, 1023, 20, 100); //mapping from 0 to 100

 
 Serial.print("LDR Value is: ");
 Serial.println(inputVal);

 
  }




