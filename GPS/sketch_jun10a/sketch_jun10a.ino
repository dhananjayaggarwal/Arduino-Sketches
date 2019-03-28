/*
gps code from: https://create.arduino.cc/projecthub/ruchir1674/how-to-interface-gps-module-neo-6m-with-arduino-8f90ad

gsm code from: https://circuitdigest.com/microcontroller-projects/send-data-to-web-server-using-sim900a-arduino
about tinyGps: http://forum.arduino.cc/index.php?topic=37097.0
               https://www.pjrc.com/teensy/td_libs_TinyGPS.html
*/



#include <LiquidCrystal.h>
#include <SoftwareSerial.h> 
#include <TinyGPS.h>

String url="";
String ip="\"esptoweb.000webhostapp.com\"";        // sparkfun server ip or url
int port=80;                              // sparkfun server port

String SendCmd="AT+CIPSEND=";           // sending number of byte command
String Start="AT+CIPSTART=\"TCP\"";     // TCPIP start command 


SoftwareSerial Serial1(7, 8); // RX, TX  // connect gsm Tx at D7 and Rx at D8

float lat = 28.5458,lon = 77.1703; // create variable for latitude and longitude object  
SoftwareSerial gpsSerial(3,4);//rx,tx 
//LiquidCrystal lcd(A0,A1,A2,A3,A4,A5); 
TinyGPS gps; // create gps object 


void setup(){ 
Serial.begin(9600); // connect serial 
  Serial1.begin(9600);    // init serial1 for GSM
//Serial.println("The GPS Received Signal:"); 
gpsSerial.begin(9600); // connect gps sensor 

  initGSM();      // init GSM module

  initGPRS();     // init GPRS in GSM Module
 
  delay(2000);


} 



void loop(){ 
  while(gpsSerial.available()){ // check for gps data 
  if(gps.encode(gpsSerial.read()))// encode gps data 
  {  
  gps.f_get_position(&lat,&lon); // get latitude and longitude 
  // display position 

 } 
} 
String latitude = String(lat,6); 
  String longitude = String(lon,6); 
Serial.println(latitude+";"+longitude); 
sendCoordinates(longitude, lattitude);
delay(1000); 
} 



void sendToServer(String str)
{
  Serial1.println(str);
  delay(1000);
}

void initGSM()
{
  connectGSM("AT","OK");
  connectGSM("ATE1","OK");
  connectGSM("AT+CPIN?","READY");
}
void initGPRS()
{
  connectGSM("AT+CIPSHUT","OK");
  connectGSM("AT+CGATT=1","OK");
  connectGSM("AT+CSTT=\"airtelgprs.com\",\"\",\"\"","OK");    //www for vodafone, airtelgprs.com
  connectGSM("AT+CIICR","OK");
  delay(1000);
  Serial1.println("AT+CIFSR");
  delay(1000);
}

void connectGSM (String cmd, char *res)
{
  while(1)
  {
    Serial.println(cmd);
    Serial1.println(cmd);
    delay(500);
    while(Serial1.available()>0)
    {
      if(Serial1.find(res))
      {
        delay(1000);
        return;
      }
    }
    delay(1000);
   }
 }


void sendCoordinates(float longitude, float lattitude){

   url="GET /input.php/";
      url+="?longi=";
      url+=longitude;
      url+="&latti=";
      url+=lattitude;
      url+=" HTTP/1.0\r\n\r\n";
      String svr=Start+","+ip+","+port;
      delay(1000);
      connectGSM(svr,"CONNECT");
      delay(1000);
      int len = url.length();
      String str="";
      str=SendCmd+len;
      sendToServer(str);
       Serial1.print(url);
      delay(1000);
      Serial1.write(0x1A);
      delay(1000);
}    




