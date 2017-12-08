#include "StepperMotor.h"

StepperMotor::StepperMotor(){
}

void StepperMotor::setup(int myStepPin, int myDirPin) {
  stepPin = myStepPin;
  dirPin = myDirPin;
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
}

void StepperMotor::setRPM(int myRPM){
  stepDelay = 1000*60/(myRPM*200);      //calculate the delay between steps based on the given RPM
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

int StepperMotor::findFlame(){
  
}

