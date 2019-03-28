#include <VirtualWire.h> // khai báo thư viện VirtualWire
#include <AFMotor.h>
byte msg[VW_MAX_MESSAGE_LEN];// biến lưu dữ liệu nhận được
byte msgLen = VW_MAX_MESSAGE_LEN;
char forward[1] = {1};
/*
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
*/



void setup()
{
  Serial.begin(115200);
  Serial.println("READY..........");
  vw_setup(2048); // cài đặt tốc độ truyền tín hiệu
  vw_set_rx_pin(2);// cài đặt chân digital để nhận tín hiệu
  vw_rx_start();// bắt đầu nhận tín hiệu
 
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
 
  
}


void loop()
{
  if (vw_get_message(msg, &msgLen)) // nếu có tín hiệu được truyền đến
  {
    //Serial.print("got transmition");
  /*  motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor3.setSpeed(255);
    motor4.setSpeed(255);  */
    switch (msg[0])
    {
   
      case '1':
        {
    /*      motor1.run(FORWARD);
          motor2.run(FORWARD);
          motor3.run(FORWARD);
          motor4.run(FORWARD);  */
          digitalWrite(12, HIGH);
          break;
        }

      case '2':
        {
    /*      motor1.setSpeed(150);
          motor2.setSpeed(150);
          motor3.setSpeed(150);
          motor4.setSpeed(150);
          motor1.run(FORWARD);
          motor2.run(FORWARD);
          motor3.run(BACKWARD);
          motor4.run(BACKWARD);  */
          digitalWrite(11, HIGH);
          break;
        }

      case '3':
        {
     /*     motor1.setSpeed(150);
          motor2.setSpeed(150);
          motor3.setSpeed(150);
          motor4.setSpeed(150);
          motor1.run(BACKWARD);
          motor2.run(BACKWARD);
          motor3.run(FORWARD);
          motor4.run(FORWARD); */
          digitalWrite(10, HIGH);
          break;
        }

      case '4':
        {
      /*    motor1.run(BACKWARD);
          motor2.run(BACKWARD);
          motor3.run(BACKWARD);
          motor4.run(BACKWARD);  */
          digitalWrite(9, HIGH);
          break;
        }


      case '0':
        {
     /*     motor1.setSpeed(70);
          motor2.setSpeed(70);
          motor1.run(FORWARD);
          motor2.run(FORWARD);
          motor3.run(FORWARD);
          motor4.run(FORWARD); */
         
          digitalWrite(12, LOW);
          digitalWrite(11, LOW);
          digitalWrite(10, LOW);
          digitalWrite(9, LOW);
          
          break;
        }
    }

  }
  /* else
    {
     motor1.run(RELEASE);
     motor2.run(RELEASE);
     motor3.run(RELEASE);
     motor4.run(RELEASE);
    } */

}
