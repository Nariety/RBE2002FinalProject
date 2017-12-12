#include "StepperMotor.h"

StepperMotor::StepperMotor(){
}

void StepperMotor::setup(int myStepPin, int myDirPin) {
  stepPin = myStepPin;
  dirPin = myDirPin;
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(stepperZero, INPUT_PULLUP);
  s.attach(11);
}

void StepperMotor::setRPM(int myRPM){
  stepDelay = 1000*60/(myRPM*stepsPerRevolution);      //calculate the delay between steps based on the given RPM
}

void StepperMotor::zeroSelf(){
  if(stepCount){  //when the stepper has taken steps
    takeSteps(-stepCount);
  }
  else{           //when the stepper is first initialized
    while(digitalRead(stepperZero)){//while the limit switch is not triggered
      takeSteps(-1);
    }
  }
}

void StepperMotor::takeSteps(int steps){
  if(steps>0){
    digitalWrite(dirPin,HIGH);
    for(int i = 0; i < steps; i++){
      digitalWrite(stepPin,HIGH);
      delay(stepDelay);
      digitalWrite(stepPin,LOW);
      delay(stepDelay);
    }
  }
  else{
    digitalWrite(dirPin,LOW);
    for(int i = steps; i > 0; i--){
      digitalWrite(stepPin,HIGH);
      delay(stepDelay);
      digitalWrite(stepPin,LOW);
      delay(stepDelay);
    }
  }
  
}

int StepperMotor::findFlame(int range){
  int lowestPoint = 1023;
  int lowestPointBuffer = 0;
  int lowestStep = 0;
  takeSteps(-(range/2));
  for(int i = 0;i<range;i++){
    takeSteps(1);
    stepCount++;
    lowestPointBuffer = analogRead(flameSensorPin);
    if(lowestPointBuffer < lowestPoint){
      lowestPoint = lowestPointBuffer;
      lowestStep = -(range/2) + stepCount;
    }
  }
  //return lowestPoint;
  return lowestStep;
}

void StepperMotor::findFlameServo(int range){
  int inc = 5;
  int servoVal = 55;
  int lowPoint = findFlame(range);
  while(digitalRead(stepperZero)){  //while the limit switch is not triggered
    takeSteps(-1);
  }
  takeSteps(range/2);
  takeSteps(lowPoint);
  if(servoVal >= 140){
    inc = -3;
  }else if(servoVal <= 20){
    inc = 3;
  }
  if(analogRead(A1) > 40){
    servoVal += inc;
    s.write(servoVal);
  }else{
      digitalWrite(24, HIGH);
      delay(3000);
      digitalWrite(24, LOW);
  }
  delay(50);
}

void StepperMotor::hold(){
  digitalWrite(stepPin, LOW);
}

