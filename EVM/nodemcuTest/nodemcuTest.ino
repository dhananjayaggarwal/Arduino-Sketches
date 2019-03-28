/*
 *  ESP8266 JSON Decode of server response
 *  -Manoj R. Thkuar
 *  https://circuits4you.com
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* wifiName = "aggarwal";
const char* wifiPass = "air27101";

//Web Server address to read/write from 
const char *host = "http://ievm.ml/jsonCandidates.php";

void setup() {
  
  Serial.begin(9600);
  delay(10);
  Serial.println();
  
  Serial.print("Connecting to ");
  Serial.println(wifiName);

  WiFi.begin(wifiName, wifiPass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
  nothing();
}

void nothing(){
 HTTPClient http;    //Declare object of class HTTPClient

  Serial.print("Request Link:");
  Serial.println(host);
  
  http.begin(host);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload from server

  Serial.print("Response Code:"); //200 is OK
  Serial.println(httpCode);   //Print HTTP return code

  Serial.print("Returned data from Server: i.e payload");
  Serial.println(payload);    //Print request response payload
  Serial.println("  ");
  Serial.println(payload);    //Print request response payload
  Serial.println("  ");

  /* pos1 is the index of the opening bracket and pos2 is the index of closing bracket. 
    In this example we have just one opening and closing curly bracket so there is no issue to check for first and last bracket
    so i used indexof function directly to find fisrt index of each.
    After positions are known, remove string before opening curly bracket and after closing bracket*/
  String jpayload = "hello {\"option1\":\"BJP\",\"option2\":\"AAP\",\"option3\":\"INC\",\"option4\":\"Others\"} dios";
  Serial.print("JLength "); Serial.println(jpayload.length());
  int pos1 = jpayload.indexOf("{");
  int pos2 = jpayload.indexOf("}");
  Serial.print("Pos1: "); Serial.println(pos1);
  Serial.print("Pos2: "); Serial.println(pos2);
  if(pos2!= jpayload.length()){
  jpayload.remove(pos2+1); //remove everything after the closing bracket
  }
  if(pos1>0){
  jpayload.remove(0,pos1); //remove everything from starting to one before the opening bracket https://www.arduino.cc/en/Tutorial/StringRemove
  }
  

  int pos1n = jpayload.indexOf("{");
  int pos2n = jpayload.indexOf("}");
  Serial.print("Pos1n: "); Serial.println(pos1n);
  Serial.print("Pos2n: "); Serial.println(pos2n);
  Serial.print("JLength New: "); Serial.println(jpayload.length());
  
  Serial.println(jpayload);
  
  if(httpCode == 200)
  {
    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
   const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
   DynamicJsonBuffer jsonBuffer(capacity);

  const char* json = "{\"option1\":\"BJP\",\"option2\":\"AAP\",\"option3\":\"INC\",\"option4\":\"Others\"}";

   // Parse JSON object
    JsonObject& root = jsonBuffer.parseObject(jpayload);
    if (!root.success()) {
      Serial.println(F("Parsing failed!"));
      return;
    }
  
    // Decode JSON/Extract values
    Serial.println(F("Response:"));
    Serial.println(root["option1"].as<char*>());
    Serial.println(root["option2"].as<char*>());
    Serial.println(root["option3"].as<char*>());
    Serial.println(root["option4"].as<char*>());
  }
  else
  {
    Serial.println("Error in response");
  }

  http.end();  //Close connection

  
}

void loop() {
 
  
  delay(10000);  //GET Data at every 5 seconds
  delay(10000);
  delay(10000);
  delay(10000);
  delay(10000);
  delay(10000);
  while(1);
}
