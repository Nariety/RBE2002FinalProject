#include "StepperMotor.h"

StepperMotor::StepperMotor() {
}

void StepperMotor::setup(int myStepPin, int myDirPin) {
  stepPin = myStepPin;
  dirPin = myDirPin;
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepperZero, INPUT_PULLUP);
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

void StepperMotor::findFlameServo(int range){
  int inc = 3;
  int servoVal = 55;
  //zeroSelf();
  //takeSteps(range/2);
  int lowPoint = findFlame(range);
  while(digitalRead(stepperZero)){  //while the limit switch is not triggered
    takeSteps(1);
  }
  takeSteps(-30);
  //exit(0);
  takeSteps(lowPoint);
  boolean flag = true;
  while(flag){
    if(servoVal >= 140){
      inc = -3;
    }else if(servoVal <= 20){
      inc = 3;
    }
    if(analogRead(A1) > 40){
      servoVal += inc;
      s.write(servoVal);
    }else{
        flag = false;
        digitalWrite(24, HIGH);
        delay(3000);
        digitalWrite(24, LOW);
    }
    delay(50);
  }
}

int StepperMotor::findFlame(int range) {
  int lowestPoint = 1023;
  int lowestPointBuffer = 0;
  int stepCountBuffer = 0;
  zeroSelf();
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
  digitalWrite(stepPin, LOW);
}

