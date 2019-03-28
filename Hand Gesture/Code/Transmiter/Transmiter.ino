#include <VirtualWire.h> // khai báo thư viện VirtualWire
#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
//#define OUTPUT_READABLE_ACCELGYRO
#define OUTPUT_BINARY_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;
char text[5] = "";// khai báo string dạng array
byte i = 0;

void setup()
{
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  Serial.begin(9600);// giao tiếp Serial với baudrate 9600
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  Serial.println("Ready.........");
  vw_set_ptt_inverted(true);// yêu cầu cho RF link modules
  vw_setup(2048);// cài đặt tốc độ truyền tín hiệu
  vw_set_tx_pin(8);// cài đặt chân digital để phát tín hiệu
  pinMode(LED_PIN, OUTPUT);

}

void loop()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
#ifdef OUTPUT_READABLE_ACCELGYRO
  // display tab-separated accel/gyro x/y/z values
  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");   //-32000
  Serial.println(gz);
  //delay(250);
#endif

#ifdef OUTPUT_BINARY_ACCELGYRO
  /*  Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
    Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
    Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
    Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
    Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
    Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF)); */
#endif


  if ((ay < 9000) and (ay > -9000) and (ax < 12000) and (ax > -3000))
  {
    text[i] = '0';
    vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
    vw_wait_tx();

  }

  if (ax < -3800)
  {
    if (ay < -13000)
    {
      text[i] = '5'; // tới phải
      vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
      vw_wait_tx();
    }
    else if (ay > 8000)
    {
      text[i] = '6'; // tới trái
      vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
      vw_wait_tx();
    }
    else
    {
      text[i] = '1'; //tới
      vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
      vw_wait_tx();
    }
  }

  if (ay < -13000)
  {
    if (ax < -3800)
    {
      text[i] = '5'; // tới phải
      vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
      vw_wait_tx();
    }
    else
    {
      text[i] = '2'; // phải
      vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
      vw_wait_tx();
    }
  }

  if (ay > 7000)
  {
    if (ax < -3800)
    {
      text[i] = '6'; // tới trái
      vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
      vw_wait_tx();
    }
    else
    {
      text[i] = '3'; //  trái
      vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
      vw_wait_tx();
    }
  }

  if (ax > 14000)
  {
    text[i] = '4'; //lùi
    vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
    vw_wait_tx();
  }



  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);

}
