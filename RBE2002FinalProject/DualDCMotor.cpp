
#include "DualDCMotor.h"

//Encoder leftEnc(2);
//Encoder rightEnc(3);

DualDCMotor::DualDCMotor() {

}

void DualDCMotor::setup() {
  // set up motor pins
  pinMode(leftMotorFor, OUTPUT); 
  pinMode(leftMotorRev, OUTPUT);
  pinMode(rightMotorFor, OUTPUT);
  pinMode(rightMotorRev, OUTPUT);
  digitalWrite(leftMotorFor, 0);
  digitalWrite(leftMotorRev, 0);
  digitalWrite(rightMotorFor, 0);
  digitalWrite(rightMotorRev, 0);
  // set up ultrasonic sensors
  pinMode(MaxBotixPin, OUTPUT);
  leftULS.setup(9, 10);
//  rightULS.setup(0, 1);
  imu.setup();
  Serial.println("IMU set up finished");
  // set up pid control for driving
  pidTurn.setpid(1, 0.01, 0.01);
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


// drive straight while following the wall on the left side
void DualDCMotor::driveAlongWall() {
  lastTime = millis();
  // start driving the robot forward
  setMotorSpeed(1, PWM);
  setMotorSpeed(0, PWM);
  // when the wall in front is far enough, the line sensor is not detecting an edge, and leftULS is detecting a wall
  while (analogRead(MaxBotixPin) > 10 && analogRead(lineSensorPin) > 500 && leftULS.Range() < 8) {
    if (millis() - lastTime >= 200) {
      sideError = leftULS.Range() - setDis;
      if (sideError > 0) {
        setMotorSpeed(0, PWM - sideError * 20);
      }
      else if (sideError < 0) {
        setMotorSpeed(1, PWM - sideError * 20);
      }
      lastTime = millis();
    }
  }
  stopMotors();
}

void DualDCMotor::turnRight() {
  float currentAngle = imu.getGyroZ();
  float targetAngle = 90 + currentAngle;
  float velocity = 0;
  while (targetAngle > currentAngle) {
    if (millis() - lastTime > 200) {
      velocity = pidTurn.calc(targetAngle, currentAngle);
      setMotorSpeed(0, velocity);
      setMotorSpeed(1, -velocity);
      currentAngle = imu.getGyroZ();
      imu.updateIMU();
      lastTime = millis();
    }
  }
  stopMotors();
}

void DualDCMotor::turnLeft() {
  float currentAngle = imu.getGyroZ();
  float targetAngle = currentAngle - 90;
  float velocity = 0;
  while (targetAngle < currentAngle) {
    if (millis() - lastTime > 200) {
      velocity = pidTurn.calc(targetAngle, currentAngle);
      setMotorSpeed(0, velocity);
      setMotorSpeed(1, -velocity);
      currentAngle = imu.getGyroZ();
      imu.updateIMU();
      lastTime = millis();
    }
  }
  stopMotors();
}

// drive straight with encoder
void DualDCMotor::driveStraight() {
  double prevPosition = leftEncTicks;
  while (analogRead(lineSensorPin) > 500 && leftEncTicks-prevPosition > ticksToPassWall) {
    setMotorSpeed(0, PWM / 2);
    setMotorSpeed(1, PWM / 2);
  }
  stopMotors();
}

void DualDCMotor::stopMotors() {
  setMotorSpeed(0, 0);
  setMotorSpeed(1, 0);
}

// set motor speed based on the given motor side and velocity
void DualDCMotor::setMotorSpeed(int rightSide, int velocity) {
  if (rightSide) {        // right motor is the target
    if (velocity > 0) {   // set the robot to go forward
      analogWrite(rightMotorFor, velocity);
      digitalWrite(rightMotorRev, LOW);
    }
    else if (!velocity) { // set the robot to stop
      digitalWrite(rightMotorFor, LOW);
      digitalWrite(rightMotorRev, LOW);
    }
    else {
      digitalWrite(rightMotorFor, LOW);
      analogWrite(rightMotorRev, velocity);
    }
  }
  else {                  // left motor is the target
    if (velocity > 0) {   // set the robot to go forward
      analogWrite(leftMotorFor, velocity);
      digitalWrite(leftMotorRev, LOW);
    }
    else if (!velocity) { // set the robot to stop
      digitalWrite(leftMotorFor, LOW);
      digitalWrite(leftMotorRev, LOW);
    }
    else {
      digitalWrite(leftMotorFor, LOW);
      analogWrite(leftMotorRev, velocity);
    }
  }
}


