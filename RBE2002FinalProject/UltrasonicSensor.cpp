#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int myTrigPin, int myEchoPin){
  trigPin = myTrigPin;
  echoPin = myEchoPin;
}

void UltrasonicSensor::setup() {
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
//  pinMode(led, OUTPUT);
//  pinMode(led2, OUTPUT);
}

long UltrasonicSensor::Range() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / meterPerSecond;
  return distance;
}
