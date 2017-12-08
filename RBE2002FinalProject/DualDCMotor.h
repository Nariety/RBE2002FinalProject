#include "Arduino.h"
#include <Motors2.h>
#include <Servo.h>
#include <Encoder.h>
#include "PID_RBE.h"
#include "UltrasonicSensor.h"
#include "IMU.h"


class DualDCMotor{
  public:
  DualDCMotor();
  void setup();
  double calcVel();
  void driveStraight();
  
  private:
  PID_RBE pidDrive;
  PID_RBE pidTurn;
  // Initialize MaxBotix Ultrasonic Sensor
  const int MaxBotixPin = A0;
  
  // Initialize UltrasonicSensor*2
  UltrasonicSensor leftULS;
  UltrasonicSensor rightULS;

  // Initialize DC Motor control pins
  const int leftMotor = 5;
  const int rightMotor = 6;

  // Initialize Popolu Line Sensor
  const int lineSensorPin = A15;

  double setDis = 6;
  double curTime=0;
  double prevTime=0;
  double timeInterval=0;
  double movement=0;
  double ticksToDeg= 0.1125;//0.2206;
  double Vel = 0;
  double prevPos;
  long lastTime=0;
  
  int PWM = 0;
  int prevPWM = 0;
  int sideError = 0;

};

