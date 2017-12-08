#include <Stepper.h>
#include "StepperMotor.h"
#include "DualDCMotor.h"

// Initialize Stepper motor
const int stepsPerRevolution = 200;

StepperMotor fanStepper;
/* stepper motor functions
 * setSpeed(rpm); set the stepper motor turning speed
 * steps(steps);  turn the stepper motor for the given steps,negative for C
 */

// Initialize IRS for Stepper Zeroing and START/STOP
const int start_stop = 18;
const int stepperZero = 3;

// Initialize drivetrain motors
DualDCMotor drivetrain;

// Initialize fan relay
const int fanRelayPin = 4;

// Initialize fan servo 
const int fanServoPin = 11;

int stepperFlame = 0;
int servoFlame = 0;

void findFlame(){
  fanStepper.takeSteps(stepperTurn);
}

void setup() {
  drivetrain.setup();
  fanStepper.setup(8,9);
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
