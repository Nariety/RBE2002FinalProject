/*
 * Messages.h
 *
 *  Created on: 10/1/16
 *      Author: joest
 */
#include "PID.h"
#include "Arduino.h"

//Class constructor
PID::PID(){
  
}

//Function to set PID gain values
void PID::setpid(float P, float I, float D){
  kp=P;
  ki=I;
  kd=D;
}

//Write this function to calculate a control signal from the set velocity 
//and the current velocity 
float PID::calc(double setVel, double curVel){
  // calculate error
  double error = curVel - setVel;
  // calculate derivative of error
  double dError = error - last_error;
  // calculate integral error. Running average is best but hard to implement
  sum_error += error;
  // sum up the error value to send to the motor based off gain values. 
  float pid = (error * kp + dError * kd + sum_error * ki)*-1;
  // limit control value to 0-254
  if(pid > 254){
    pid = 254;
  }
  else if (pid < 0){
    pid = 0;
  }
  last_error = error;
  //return the control signal
  return pid;
}
