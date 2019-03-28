#include <ESP8266WiFi.h>

const char* ssid     = "Name-of-WiFi";
const char* password = "password";
const char* host = "esptoweb.000webhostapp.com";  //Name of website where you need to send data


const int analog_ip = A0; //Naming analog input pin
int inputVal  = 0;        //Variable to store analog input values

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(2, HIGH); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  

}

void ldrRead();   //Function to read LDR values
void MinuteDelay(int number);   //Function to provide delay in N minutes

void loop() {

  delay(1000);
 

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  

ldrRead();
delay(500);

      
   
        // We now create a URI for the request
        //use your page where php script is running in place of /connection.php
       String url = "/connection.php";
        url += "?Intensity=";
        url += inputVal;
        
        
        Serial.print("Requesting URL: ");
        Serial.println(url);
        
        // This will send the request to the server, here header is generated
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" + 
                     "Connection: close\r\n\r\n");
        unsigned long timeout = millis();
        while (client.available() == 0) {
          if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
          }
        }
        
        // Read all the lines of the reply from server and print them to Serial
        while(client.available()){
          String line = client.readStringUntil('\n');   // \n is used as terminator
          Serial.println(line);
          
        }
        Serial.println();
        Serial.println("closing connection");


   
    //Wait for nearly 5 minutes
   MinuteDelay(5);  
    
 
}


void ldrRead()
{
  
  inputVal = analogRead (analog_ip); // Analog Values 0 to 1023
inputVal = map(inputVal, 0, 1023, 20, 100); //mapping from 20 to 100

 
 Serial.print("LDR Value is: ");  //Just to print value of LDR on serial monitor
 Serial.println(inputVal);
 
  
  
  }


void MinuteDelay(int number){
  for (int i = 0; i < number; ++i)
    {
      
      // use 10 second delay six times for each minute 
      for(int j=0; j<6 ;j++)
      {
        
        // yield();
        delay(10000);
        
      }
    }
  }
