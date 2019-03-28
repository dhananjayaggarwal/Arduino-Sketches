
/*
 Program To rotate stepper motor of rotating structure
1. Move the Rotating Structure in clockwise direction by 90 deg.
2.  Stop for 200msec.
3.  Move the Rotating Structure again in clockwise direction by 180 deg.
4.   Stop for 200msec.
5.  Move the Rotating Structure in clockwise direction by 90 deg.



 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int i = 1;

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
  delay(1000);

 
  
}

void loop() {

  if(i==1){
  
     // step one revolution  in one direction:
  Serial.println("90 degree clockwise");
  myStepper.step(65);
  delay(200);
  
  Serial.println("180 degree clockwise");
  myStepper.step(115);
  delay(200);  

  Serial.println("90 degree clockwise");
  myStepper.step(65);
  delay(200);
  i++;
  
  }
  }
  


