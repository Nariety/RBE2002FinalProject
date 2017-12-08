#include "Arduino.h"
#include <Motors2.h>
#include "PID_RBE.h"
#include <Servo.h>
#include <Encoder.h>

class DCMotor{
  public:
  DCMotor();
  void setup(int myStepPin, int myDirPin);
  void setRPM(int myRPM);
  void takeSteps(int steps);
  
  private:
  Encoder myEnc(2, 3);
  int stepPin;
  int dirPin;
  PID_RBE pidCon;
  double setVel=90;
  double curTime=0;
  double prevTime=0;
  double timeInterval=0;
  double movement=0;
  double ticksToDeg= 0.1125;//0.2206;
  double prevPos;
  long lastTime=0;
  long lastTime2=0;
  double Vel;
  float velocity;
  float RPM;
  float current;
  float PWM;
  float analogWriteVal;
};

