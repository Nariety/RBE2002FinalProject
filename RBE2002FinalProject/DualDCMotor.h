#include "Arduino.h"
#include <Motors2.h>
#include <Servo.h>
//#include <Encoder.h>
#include "PID_RBE.h"
#include "UltrasonicSensor.h"
#include "IMU.h"


class DualDCMotor {
  public:
    DualDCMotor();
    void setup();
    double calcLeftVel();
    double calcRightVel();
    void driveStraight();
    void LeftEnc();
    void RightEnc();

    int leftEncTicks = 0;
    int rightEncTicks = 0;

  private:
    PID_RBE pidDrive;
    PID_RBE pidTurn;
    // Initialize MaxBotix Ultrasonic Sensor
    const int MaxBotixPin = A0;

    // Initialize UltrasonicSensor*2
    UltrasonicSensor leftULS;
    UltrasonicSensor rightULS;

    // Initialize DC Motor control pins
    const int leftMotorPin = 5;
    const int rightMotorPin = 6;
    const int leftEncPin = 2;
    const int rightEncPin = 3;

    // Initialize Popolu Line Sensor
    const int lineSensorPin = 15; /*****************************/

    double setDis = 6;
    double curTime = 0;
    double prevTime = 0;
    double timeInterval = 0;
    double movement = 0;
    double ticksToDeg = 0.1125; //0.2206;
    double Vel = 0;
    double prevPos;
    long lastTime = 0;

    int PWM = 0;
    int prevPWM = 0;
    int sideError = 0;
};

