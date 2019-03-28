#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ); // tạo động cơ #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

void setup() {


  motor1.setSpeed(255);     // chọn tốc độ maximum 255`/255
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
}

void loop() {

  //    Serial.print("tien");

  motor1.run(FORWARD);      // động cơ tiến
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(2000);

  //  Serial.print("lui");

  motor1.run(RELEASE);      //   dừng động cơ
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(2000);


  motor1.run(BACKWARD);     // động cơ lùi
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(2000);

  //   Serial.print("tack");

  motor1.run(RELEASE);      //   dừng động cơ
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(2000);

}
