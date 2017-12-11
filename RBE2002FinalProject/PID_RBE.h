/*
   Messages.h

    Created on: 10/1/16
        Author: joest
*/

#ifndef PID_RBE_H_
#define PID_RBE_H_

class PID_RBE {
  public:
    PID_RBE();
    void setpid(float P, float I, float D);
    //calculate the output control signal
    float calc(double setVel, double curVel);

  private:
    //set PID constants
    float kp;
    float ki;
    float kd;
    float last_error = 0;
    float all_errors[10];
    float sum_error = 0;
    int errorCount = 0;
};



#endif
