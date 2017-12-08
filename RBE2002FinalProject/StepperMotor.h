#include "Arduino.h"

class StepperMotor{
  public:
  StepperMotor();
  void setup(int myStepPin, int myDirPin);
  void setRPM(int myRPM);
  void takeSteps(int steps);
  int findFlame();

  int flameX = 0;
    
  private:
  int stepPin;
  int dirPin;
  int flameSensorPin = A1;

  int stepDelay = 60;
const int stepsPerRevolution = 200;     // since there will only be one stepper motor, the steps per revolution is hardcoded in
const int stepperTurn = 25;          //number of steps for a 45 degree turn
};

