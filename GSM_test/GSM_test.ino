
 #include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}



void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 'a':
      Sendat();
      break;
    
    case 's':
      SendMessage();
      break;
     case 'r':
      RecieveMessage();
      break;
 
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}


 void SendMessage()
{
   
mySerial.println("AT+CLIP=1");
delay(1000);
  
}
void Sendat()
{
  
mySerial.println("AT");
delay(1000);
  
}

void RecieveMessage()
{
  
  mySerial.println("AT+CLCC");
delay(1000);
  }


