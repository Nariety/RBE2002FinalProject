
#include "DualDCMotor.h"

//Encoder leftEnc(2);
//Encoder rightEnc(3);

DualDCMotor::DualDCMotor() {

}

void DualDCMotor::setup() {
  // set up motor pins
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  analogWrite(leftMotorPin, 0);
  analogWrite(rightMotorPin, 0);
  // set up ultrasonic sensors
  pinMode(MaxBotixPin, OUTPUT);
  leftULS.setup(9, 10);
  rightULS.setup(0, 1);

  // set up pid control for driving
  pidDrive.setpid(1, 0.01, 0.01);
  //pidCon.setpid(1,0.01,0.001);
}
// Returns Vel in degress/second
double DualDCMotor::calcLeftVel() {
  //current positions
  double curPos = leftEncTicks;
  //current time
  curTime = millis();
  //time change in ms from last call
  timeInterval = curTime - prevTime;
  //encoder ticks since last call
  movement = curPos - prevPos;
  //encoder ticks to degrees
  movement = movement * ticksToDeg;
  //Velocity in degrees per milliseconds
  Vel = movement * 1000 / timeInterval;
  //sets curent vals to previous
  prevPos = curPos;
  prevTime = curTime;
  return Vel;
}

double DualDCMotor::calcRightVel() {
  //current positions
  double curPos = rightEncTicks;
  //current time
  curTime = millis();
  //time change in ms from last call
  timeInterval = curTime - prevTime;
  //encoder ticks since last call
  movement = curPos - prevPos;
  //encoder ticks to degrees
  movement = movement * ticksToDeg;
  //Velocity in degrees per milliseconds
  Vel = movement * 1000 / timeInterval;
  //sets curent vals to previous
  prevPos = curPos;
  prevTime = curTime;
  return Vel;
}


// drive straight while following the wall on the right side
void DualDCMotor::driveStraight() {
  if (millis() - lastTime >= 200) {
    PWM = pidDrive.calc(setDis, analogRead(MaxBotixPin));
    if (prevPWM != PWM) {
      analogWrite(leftMotorPin, PWM);
      analogWrite(rightMotorPin, PWM);
    }

    sideError = rightULS.Range() - setDis;
    if (sideError > 0) {
      analogWrite(rightMotorPin, PWM - sideError);
    }
    else if (sideError < 0) {
      analogWrite(leftMotorPin, PWM + sideError);
    }

    //Calculates the dutycycle of the PWM 0-1
    //  PWM = analogWriteVal/255;

    //Sets the lastTime variable
    lastTime = millis();
  }

  //stop all motor movement
  void DualDCMotor::stopMotors(){
    analogWrite(leftMotorPin, 0);
    analogWrite(rightMotorPin, 0);
  }
}


