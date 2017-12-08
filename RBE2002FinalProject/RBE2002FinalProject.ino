#include <Stepper.h>
#include "StepperMotor.h"
#include "UltrasonicSensor.h"

// Initialize Stepper motor
const int stepsPerRevolution = 200;
const int stepperTurn = 25;       //number of steps for a 45 degree turn
StepperMotor fanStepper(8,9);
/* stepper motor functions
 * setSpeed(rpm); set the stepper motor turning speed
 * steps(steps);  turn the stepper motor for the given steps,negative for C
 */

// Initialize MaxBotix Ultrasonic Sensor
const int MaxBotixPin = A0;

// Initialize UltrasonicSensor*2
UltrasonicSensor leftULS(4,5);
UltrasonicSensor rightULS(6,7);

void setup() {
  
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
