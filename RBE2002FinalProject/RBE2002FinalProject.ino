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

int flameDegFromCenter = 0;

enum State {STOP, FIELDSCAN, FLAMESCAN, DRIVE} state;
int prevState = STOP;

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
  attachInterrupt(digitalPinToInterrupt(19), RightEnc, RISING);
  pinMode(18, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(18), startStop, FALLING);
}

void loop() {
  switch(state){
    case STOP:  //cease all motor functions
      drivetrain.stopMotors();
      fanStepper.hold();
      break;
    case FIELDSCAN: //scan field to find general direction of flame
      flameDegFromCenter = stepToDeg(fanStepper.findFlame(60));
      break;
    case FLAMESCAN: //horizontal and vertical scan to aim fan at flame
      break;
    case DRIVE:
      break;
  }


  
}

//returns step number mapped to degrees (-45 is left, +45 is right)
int stepToDeg(int stepNum){
  return map(stepNum, -30, 30, -45, 45);
}

void startStop() {
  if(state == STOP){
    state = prevState;
    prevState = STOP;
  }else{
    prevState = state;
    state = STOP;
    drivetrain.stopMotors();
    fanStepper.hold();
  }
}


void LeftEnc() {
  drivetrain.leftEncTicks++;
}

void RightEnc() {
  drivetrain.rightEncTicks++;
}

