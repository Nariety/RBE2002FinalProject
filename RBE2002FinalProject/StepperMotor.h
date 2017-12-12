#include "Arduino.h"
#include <Servo.h>

class StepperMotor{
  public:
  StepperMotor();
  void setup(int myStepPin, int myDirPin);
  void setRPM(int myRPM);
  void zeroSelf();
  void takeSteps(int steps);
  void findFlameServo(int range);
  void hold();
  int findFlame(int range);
<<<<<<< HEAD
=======
  void hold();

>>>>>>> 40995c495d988b44148d4f64a52f243578c58085
  int flameX = 0;
    
  private:
  int stepPin;
  int dirPin;
  const int stepperZero = 25;
  int stepDelay = 60;
  const int flameSensorPin = A1;
  const int stepsPerRevolution = 200;     // since there will only be one stepper motor, the steps per revolution is hardcoded in
  int stepCount = 0;
  Servo s;
};

