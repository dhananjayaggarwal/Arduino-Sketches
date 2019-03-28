#include <Servo.h>

void moveServo(int time, int servo_target[]);
void homeo();
void dance();

#define PIN_YL 2 //servo[0]
  #define PIN_YR 3 //servo[1]
  #define PIN_RL 4 //servo[2]
  #define PIN_RR 5 //servo[3]

Servo myServo[4];


void setup() {
  // put your setup code here, to run once:
  myServo[0].attach(PIN_YL);
  myServo[1].attach(PIN_YR);
  myServo[2].attach(PIN_RL);
  myServo[3].attach(PIN_RR);
  homeo();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  dance();

}

void moveServo(int time1, int val[])
{
  delay(time1);
  for(int i=0; i<4; i++)
  {
    myServo[i].write(val[i]);
    }
    delay(time1);
  
  }

void homeo()
{
  for(int i=0; i<4; i++)
  myServo[i].write(90);  }

void dance()
{
  int a[]={80,100,0,0}, b[]={70,110,0,0};
  moveServo(15, a[4]);
  moveServo(15, b[4]);  
  }


  
