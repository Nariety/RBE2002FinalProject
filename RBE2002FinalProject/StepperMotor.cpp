#include "StepperMotor.h"

StepperMotor::StepperMotor() {
}

void StepperMotor::setup(int myStepPin, int myDirPin) {
  stepPin = myStepPin;
  dirPin = myDirPin;
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepperZero, INPUT_PULLUP);
  digitalWrite(stepPin,LOW);
  digitalWrite(dirPin,LOW);
}

void StepperMotor::setRPM(int myRPM) {
  stepDelay = 1000 * 60 / (myRPM * stepsPerRevolution); //calculate the delay between steps based on the given RPM
}

void StepperMotor::zeroSelf() {
  //when the stepper is first initialized
  while (digitalRead(stepperZero)) { //whlie the limit switch is not triggered
    takeSteps(1);
    stepCount++;
  }
  takeSteps(-34);
  
}

void StepperMotor::takeSteps(int steps) {
  if (steps > 0) {
    digitalWrite(dirPin, HIGH);
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPin, HIGH);
      delay(stepDelay);
      digitalWrite(stepPin, LOW);
      delay(stepDelay);
    }
  }
  else {
    digitalWrite(dirPin, LOW);
    for (int i = -steps; i > 0; i--) {
      digitalWrite(stepPin, HIGH);
      delay(stepDelay);
      digitalWrite(stepPin, LOW);
      delay(stepDelay);
    }
  }

}

int StepperMotor::findFlame(int range) {
  int lowestPoint = 1023;
  int lowestPointBuffer = 0;
  int stepCountBuffer = 0;
  takeSteps(-(range / 2));
  stepCount = -(range/2);
  for (int i = 0; i < range; i++) {
    takeSteps(1);
    stepCount++;
    lowestPointBuffer = analogRead(flameSensorPin);
    if (lowestPointBuffer < lowestPoint) {
      lowestPoint = lowestPointBuffer;
      stepCountBuffer = stepCount;
    }
  }
  return stepCountBuffer;
}

void StepperMotor::hold(){
  digitalWrite(stepPin,LOW);
}

