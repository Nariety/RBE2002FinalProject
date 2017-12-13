#include "StepperMotor.h"
#include "DualDCMotor.h"
#include <TimerOne.h>

// Initialize Stepper motor
const int stepsPerRevolution = 200;
const int stepperTurn = 25;          //number of steps for a 45 degree turn

StepperMotor fanStepper;
/* stepper motor functions
   setSpeed(rpm); set the stepper motor turning speed
   steps(steps);  turn the stepper motor for the given steps,negative for C
*/

// Initialize ISR for START/STOP
const int start_stop_pin = 18;

// Initialize drivetrain motors
DualDCMotor drivetrain;

// Initialize fan relay
const int fanRelayPin = 24;

// Initialize fan servo
const int fanServoPin = 11;

const int lineSensorPin = 15;

// variables for keep track of flame position
int stepperFlame = 0;
int servoFlame = 0;
int flameDegFromCenter = 0;

// timer variable
long timer = 0;
long timer2 = 0;

enum State {STOP, FIELDSCAN, FLAMESCAN, LEFTWALL, CORNER, OPENING, DRIVESTRAIGHT} state;
int prevState = STOP;

void setup() {
  Serial.begin(9600);
  fanStepper.setup(12, 13, 11);
  drivetrain.setup();
  pinMode(fanRelayPin, OUTPUT);
  digitalWrite(fanRelayPin, LOW);
  pinMode(start_stop_pin, INPUT_PULLUP);
  // set up ISR for encoders
  pinMode(19, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(19), LeftEnc, RISING);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), RightEnc, RISING);
  pinMode(18, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(18), startStop, FALLING);
  Serial.println("Robot set up finished");
  timer = millis();
}

void loop() {
  if (millis() - timer >= 50) {  // update gyro values at 20Hz
    UpdateIMU();
    timer = millis();
  }
<<<<<<< HEAD

  switch (state) {
    case STOP:  //cease all motor functions
      drivetrain.stopMotors();
      fanStepper.hold();
      break;
    case FIELDSCAN: //scan field to find general direction of flame
      drivetrain.turnRight();
      flameDegFromCenter = stepToDeg(fanStepper.findFlame(60));
      if (fanStepper.flameVal < 500) {
        drivetrain.turnTo(flameDegFromCenter);
      }
      //drive to candle
      extinguish();
      drivetrain.turnLeft();
      break;
    case FLAMESCAN: //horizontal and vertical scan to aim fan at flame
      break;
    case LEFTWALL:
      timer = drivetrain.driveAlongWall(timer);
      if(analogRead(3) < 15){
        state = CORNER;
      }else if(analogRead(lineSensorPin) < 700){
//        drivetrain.setMotorSpeed(1, -255);      //backoff
//        drivetrain.setMotorSpeed(0, -255);
//        delay(500);
//        drivetrain.stopMotors();
        timer = drivetrain.turnRight(timer);
        state = DRIVESTRAIGHT;
      }else if(drivetrain.leftULS.Range() > 20){
        state = OPENING;
      }else{
        state = FIELDSCAN;
      }
      break;
    case DRIVESTRAIGHT:
      timer = drivetrain.driveStraight(timer);
      if(analogRead(3) < 15){
        state = CORNER;
      }else if(drivetrain.leftULS.Range() < 20){
        state = LEFTWALL;
      }else if(analogRead(lineSensorPin) < 700){
//        drivetrain.setMotorSpeed(1, -255);      //backoff
//        drivetrain.setMotorSpeed(0, -255);
//        delay(500);
//        drivetrain.stopMotors();
        timer = drivetrain.turnRight(timer);
      }
      break;
=======
  if (millis() - timer2 >= 5000) {
    //      timer = drivetrain.turnRight(timer);
    //      timer = drivetrain.turnLeft(timer);
    timer = drivetrain.driveAlongWall(timer);
    //      Serial.println(drivetrain.imu.getGyroZ());
    timer2 = millis();
>>>>>>> 3fdd8c3d1748b5166d06fdd17ab3b8b1f9156aed
  }
}

//returns step number mapped to degrees (-45 is left, +45 is right)
int stepToDeg(int stepNum) {
  return map(stepNum, -30, 30, -45, 45);
}

void extinguish() {
  fanStepper.findFlameServo(60);
  Serial.println("Fan On");
  digitalWrite(fanRelayPin, HIGH);
  delay(4000);
  digitalWrite(fanRelayPin, LOW);
  Serial.println("Fan Off");
  delay(10);
}

void startStop() {
  if (state == STOP) {
    state = prevState;
    prevState = STOP;
  } else {
    prevState = state;
    state = STOP;
    drivetrain.stopMotors();
    fanStepper.hold();
  }
}

void UpdateIMU() {
  drivetrain.imu.complimentaryFilter();
}

void LeftEnc() {
  drivetrain.leftEncTicks++;
}

void RightEnc() {
  drivetrain.rightEncTicks++;
}

