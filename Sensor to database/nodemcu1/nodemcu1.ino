#include <ESP8266WiFi.h>

const char* ssid     = "ShaperJet";
const char* password = "shaperjet0284";
const char* host = "dhananjay-ecommerce.000webhostapp.com";


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

void ldrRead();
void MinuteDelay(int number);

void loop() {
  //Serial.write("OK");
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
        
       String url = "/connection.php";
        url += "?Intensity=";
        url += inputVal;
        
        
        Serial.print("Requesting URL: ");
        Serial.println(url);
        
        // This will send the request to the server
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
          String line = client.readStringUntil('\n');
          Serial.println(line);
          
        }
        Serial.println();
        Serial.println("closing connection");


   
    //Wait for nearly 5 minutes, interval is equal to 300000
   MinuteDelay(5);  
    
 
}


void ldrRead()
{
  
  inputVal = analogRead (analog_ip); // Analog Values 0 to 1023
inputVal = map(inputVal, 0, 1023, 20, 100); //mapping from 20 to 100

 
 Serial.print("LDR Value is: ");
 Serial.println(inputVal);
 
  
  
  }


void MinuteDelay(int number){
  for (int i = 0; i < number; ++i)
    {
      
      // use 6 10 second delays for each minute // with a yield before each
      for(int j=0; j<6 ;j++)
      {
        
        // yield();
        delay(10000);
        
      }
    }
  }
