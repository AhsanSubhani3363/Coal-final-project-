#include <Servo.h>

const int trigPin = 10;
const int echoPin = 11;
const int buzzer  = 5;
const int laser   = 6;

Servo myServo;

// Variables
long duration;
int distance;

int angle = 0;
int step = 2;

// Function to get distance
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(laser, OUTPUT);

  myServo.attach(12);

  Serial.begin(9600);
}

void loop() {

  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  
  if (distance > 2 && distance < 30) {

    myServo.write(angle);        
    digitalWrite(laser, HIGH);   // laser ON
    tone(buzzer, 1000);          // buzzer ON

    delay(700);                  // detection hold (unchanged)

    noTone(buzzer);              // buzzer OFF
  }

  
  else {
    digitalWrite(laser, LOW);    // laser OFF
    noTone(buzzer);              // buzzer OFF

    angle += step;

    if (angle >= 180 || angle <= 0) {
      step = -step;
    }

    myServo.write(angle);
    delay(10);   
  }
}