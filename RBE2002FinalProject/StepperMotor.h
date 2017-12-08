#include "Arduino.h"

class StepperMotor{
  public:
  StepperMotor(int myStepPin, int myDirPin);
  void setup();
  void setRPM(int myRPM);
  void takeSteps(int steps);
  
  private:
  int stepPin;
  int dirPin;
  int stepDelay = 60;
  const int stepsPerRevolution = 200;  // since there will only be one stepper motor, the steps per revolution is hardcoded in
};

