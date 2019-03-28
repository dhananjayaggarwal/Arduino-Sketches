
#include <SoftwareSerial.h>// import the serial library

SoftwareSerial mySerial(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (mySerial.available()){
BluetoothData=mySerial.read();
Serial.println(BluetoothData);
   if(BluetoothData==49){   // if number 1 pressed ....
   digitalWrite(ledpin,1);
   Serial.println("LED  On D13 ON ! ");
   }
  if (BluetoothData=='0'){// if number 0 pressed ....
  digitalWrite(ledpin,0);
   Serial.println("LED  On D13 Off ! ");
  }
}
delay(100);// prepare for next data ...
}