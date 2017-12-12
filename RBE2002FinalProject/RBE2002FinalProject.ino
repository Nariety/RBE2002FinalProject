#include "StepperMotor.h"
#include "DualDCMotor.h"

// Initialize Stepper motor
const int stepsPerRevolution = 200;
const int stepperTurn = 25;          //number of steps for a 45 degree turn

StepperMotor fanStepper;
/* stepper motor functions
   setSpeed(rpm); set the stepper motor turning speed
   steps(steps);  turn the stepper motor for the given steps,negative for C
*/

// Initialize IRS for START/STOP
const int start_stop_pin = 18;

// Initialize drivetrain motors
DualDCMotor drivetrain;

// Initialize fan relay
const int fanRelayPin = 4;

// Initialize fan servo
const int fanServoPin = 11;

int stepperFlame = 0;
int servoFlame = 0;

void findFlame() {
  fanStepper.findFlame(stepperTurn * 2);
}

void setup() {
  Serial.begin(9600);
  drivetrain.setup();
  fanStepper.setup(12, 13);
  pinMode(start_stop_pin,INPUT_PULLUP);
  // set up IRS for encoders
  pinMode(20, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(20), LeftEnc, RISING);
  pinMode(19, INPUT_PULLUP);
  attachInterrupt(digltalPinToInterrupt(19), RightEnc, RISING);
}

void loop() {
  //  // reads imu every 20ms
  //  if((millis()-timer)>=20)
  //  {
  //  complimentaryFilter();
  //  readGyro();
  //  calDis();
  //  }
  //  // prints the gyro value once per second
  //  if((millis()-timer2)>=1000)
  //  {
  //    printGyro();
  //  }
}


void LeftEnc() {
  drivetrain.leftEncTicks++;
}

void RightEnc() {
  drivetrain.rightEncTicks++;
}

