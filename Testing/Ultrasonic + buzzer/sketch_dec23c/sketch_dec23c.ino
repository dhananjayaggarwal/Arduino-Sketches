//Program To interface ultrasonic sensor and Buzzer

const int trigPin = 8;
const int echoPin = 9;
const int buzzerPin = 10;

// defines variables
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzerPin, OUTPUT); // Sets the buzzer pin as OUTPUT
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if(distance < 40 && distance >=30)
{
  digitalWrite(buzzerPin, HIGH); 
  delay(1000);
  digitalWrite(buzzerPin, LOW);
  delay(1000);
} 
else if(distance < 30 && distance >=20)
{
  digitalWrite(buzzerPin, HIGH); 
  delay(250);
  digitalWrite(buzzerPin, LOW);
  delay(250);
  }

else if(distance < 20 && distance >=10)
{
  digitalWrite(buzzerPin, HIGH); 
  delay(150);
  digitalWrite(buzzerPin, LOW);
  delay(150);
  }

else if(distance < 10 )
{
  digitalWrite(buzzerPin, HIGH); 
  
  }

  else {
     digitalWrite(buzzerPin, LOW);
    }



}
