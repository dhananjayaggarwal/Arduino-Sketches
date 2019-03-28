/*************************************************** 
  This is an example sketch for our optical Fingerprint sensor

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/


#include <Adafruit_Fingerprint.h>

int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire) my YELLOW
// pin #3 is OUT from arduino  (WHITE wire) my WHITE
SoftwareSerial mySerial(2, 3);


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  while(!Serial);
  Serial.begin(9600);
  Serial.println("Fingerprint template extractor");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }

  // Try to get the templates for fingers 1
  for (int finger = 0; finger < 5; finger++) {
    downloadFingerprintTemplate(finger);
  }
}



uint8_t downloadFingerprintTemplate(uint16_t id)
{
  Serial.println("------------------------------------");
  Serial.print("Attempting to load #"); Serial.println(id);
  uint8_t p = finger.loadModel(id);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("Template "); Serial.print(id); Serial.println(" loaded");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_BADLOCATION:
      Serial.println("Bad Location error");
      return p;
    default:
      Serial.print("Unknown error "); Serial.println(p);
      return p;
  }

  // OK success!

 // one data packet is 267 bytes. in one data packet, 11 bytes are 'usesless' :D
  uint8_t bytesReceived[556]; // 2 data packets
  memset(bytesReceived, 0xff, 556);

  Serial.print("Attempting to get #"); Serial.println(id);
 Serial.print("sTART time: "); Serial.println(millis());
 finger.getModel();
 

  uint32_t starttime = millis();

  int i = 0;
 
  while (i < 556 && (millis() - starttime) < 20000) {
      if (mySerial.available()) {
          bytesReceived[i++] = mySerial.read();
      }
  }
  Serial.print("Endtime: "); Serial.println(millis());
  Serial.print(i); Serial.println(" bytes read.");
/*  Serial.println("Decoding packet...");

  uint8_t fingerTemplate[512]; // the real template
  memset(fingerTemplate, 0xff, 512);

  // filtering only the data packets
  int uindx = 9, index = 0;
  while (index < 534) {
      while (index < uindx) ++index;
      uindx += 256;
      while (index < uindx) {
          fingerTemplate[index++] = bytesReceived[index];
      }
      uindx += 2;
      while (index < uindx) ++index;
      uindx = index + 9;
  }
  for (int i = 0; i < 512; ++i) {
      //Serial.print("0x");
      printHex(fingerTemplate[i], 2);
      //Serial.print(", ");
  }
  Serial.println("\ndone.");
*/
  Serial.println("\nBytes received.");

    for (int i = 0; i < 556; ++i) {
      //Serial.print("0x");
      printHex(bytesReceived[i], 2);
      //Serial.print(", ");
  }

  Serial.println("\n Integer array ");
   for (int i = 0; i < 556; ++i) {
      //Serial.print("0x");
     Serial.print(bytesReceived[i]);
      Serial.print(", ");
  }

}



void printHex(int num, int precision) {
    char tmp[16];
    char format[128];
 
    sprintf(format, "%%.%dX", precision);
 
    sprintf(tmp, format, num);
    Serial.print(tmp);
}

void loop()
{}

