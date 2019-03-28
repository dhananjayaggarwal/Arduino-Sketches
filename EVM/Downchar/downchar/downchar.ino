/*
Edited By: Dhananjay
Use: To add DownChar functionality

DownChar frame Format
EF01FFFFFFFF0100040901000F
EF01 Frame identify
FFFFFFFF Module Address
01 Package Identifier (01 for instruction)
0004 Package Length (1+1+2 = 4)
09 Instruction code for DownChar
01 Buffer Number(01 or 02)
000F Check Sum for buffer 1

To Store Template of buffer 01 to id 0004
EF01FFFFFFFF010006060100040012
EF01 Frame identify
FFFFFFFF Module Address
01 Package Identifier (01 for instruction)
0006 Package Length (1+1+2+2 = 6)
06 Instruction code for StoreModel 
01 Buffer number 01
0004 Page Location i.e. id = 0004
0012 CheckSum (01 + 0006 + 06 + 01 + 0004 = 12h)


*/


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

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t data[]={3, 1, 94, 28, 128, 0, 248, 14, 248, 6, 240, 6, 224, 2, 224, 2, 224, 0, 192, 0, 192, 0, 192, 0, 224, 0, 224, 0, 224, 2, 224, 2, 224, 2, 224, 2, 224, 2, 224, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 139, 171, 254, 91, 143, 214, 94, 59, 32, 153, 190, 80, 162, 64, 222, 61, 46, 26, 30, 96, 50, 108, 254, 57, 181, 67, 94, 107, 184, 151, 222, 38, 56, 196, 158, 56, 189, 154, 190, 98, 189, 152, 222, 106, 66, 128, 214, 55, 66, 218, 94, 76, 194, 216, 222, 83, 4, 23, 63, 69, 132, 65, 119, 51, 23, 195, 63, 51, 33, 130, 191,113, 170, 85, 247, 39, 65, 218, 127, 93, 65, 215, 255, 100, 54, 23, 26, 88, 55, 65, 210, 86, 58, 91, 210, 81, 56, 3, 211, 94, 56, 1, 19, 107, 38, 105, 178, 112, 37, 20, 211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 87, 33, 127, 0, 255, 254, 255, 254, 254, 126, 248, 62, 240, 14, 240, 6, 224, 2, 224, 2, 224, 2, 192, 2, 192, 2, 192, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75, 16, 25, 30, 81, 34, 64, 222, 111, 169, 86, 62, 61, 45, 218, 190, 74, 53, 2, 158, 13, 185, 5, 62, 38, 185, 4, 222, 76, 194, 216, 222, 52, 24, 66, 223, 55, 179, 3, 63, 97, 49, 129, 188, 111, 179, 235, 84, 106, 66, 64, 92, 44, 167, 132, 85, 59, 160, 217, 186, 55, 33, 66, 218, 21, 183, 195, 218, 25, 61, 154, 218, 45, 63, 2, 218, 104, 178, 151, 27, 27, 185, 154, 115, 114, 190, 25, 248, 24, 195, 214, 216, 52, 62, 90, 25, 33, 193, 215, 89, 39, 193, 217, 25, 37, 164, 69, 118, 35, 37, 219, 177, 56, 191, 26, 87, 115, 63, 214, 113, 91, 183, 129, 85, 99, 190, 152, 117, 94, 64, 151, 178, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t data1[128]={0};
uint8_t data2[128]={0};
uint8_t data3[128]={0};
uint8_t data4[128]={0};
 
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



  //Load fingerprint to buffer 01h or 02h (buffer, id)
  downchar(0x01,3);
}



uint8_t downchar(uint8_t buffNo, uint16_t id){
    Serial.println("------------------------------------");
    Serial.print("Attempting to load template in buffer#"); Serial.println(buffNo);
    uint8_t p = finger.downModel(buffNo);
      switch (p) {
    case FINGERPRINT_OK:
      Serial.print("Ready to send template "); Serial.print(" in buffer #"); Serial.println(buffNo);
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    default:
      Serial.print("Unknown error "); Serial.println(p);
      return p;
  }
  //OK Success
  Serial.println("Attempting to send data ");
  finger.sendData(1,128, data);
  delay(100);
  finger.sendData(1, 128, (data+128));
  delay(100);
  finger.sendData(1, 128, (data+128+128));
  delay(100);
  finger.sendData(2, 128, (data+128+128+128));
  delay(100);

  Serial.println("Data Sent successfully: ");
  Serial.print("Attempting to store model at id #");Serial.println(id);

  p = finger.storeModel(id);
 if (p == FINGERPRINT_OK) {
    Serial.print("Stored! at id#");Serial.println(id);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
  




}




void loop()
{}


