#include "PID_RBE.h"
#include "Arduino.h"

//Class constructor
PID_RBE::PID_RBE(){
  
}

//Function to set PID gain values
void PID_RBE::setpid(float P, float I, float D){
  kp=P;
  ki=I;
  kd=D;
}

//Write this function to calculate a control signal from the set velocity 
//and the current velocity 
float PID_RBE::calc(double setVel, double curVel){
  // calculate error
  double error = curVel - setVel;
  // calculate derivative of error
  double dError = error - last_error;
  // calculate integral error. Running average is best but hard to implement
  sum_error = sum_error+error-all_errors[errorCount];   // replace old error with new error
  all_errors[errorCount] = error;                       // overwrites old errors, only ten of the errors are used
  errorCount = (errorCount+1)%10;
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
