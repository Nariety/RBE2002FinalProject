
#include "DualDCMotor.h"

Encoder myEnc(2, 3);

// Returns Vel in degress/second
double DualDCMotor::calcVel(){
  //current positions
  double curPos=myEnc.read();
  //current time
  curTime=millis();
  //time change in ms from last call
  timeInterval=curTime-prevTime;
  //encoder ticks since last call
  movement=curPos-prevPos;
  //encoder ticks to degrees
  movement= movement *ticksToDeg;
  //Velocity in degrees per milliseconds
  Vel=movement*1000/timeInterval;
  //sets curent vals to previous
  prevPos=curPos;
  prevTime=curTime;
  return Vel;
}

void DualDCMotor::setup() {
  pinMode(leftMotor,OUTPUT);
  pinMode(rightMotor,OUTPUT);
  analogWrite(leftMotor,0);
  analogWrite(rightMotor,0);
  Serial.begin(9600);
  pidDrive.setpid(1,0.01,0.01);
  // set up ultrasonic sensors
  pinMode(MaxBotixPin,OUTPUT);
  leftULS.setup(9,10);
  rightULS.setup(0,1);
  
  //pidCon.setpid(1,0.01,0.001);
}

// drive straight while following the wall on the right side
void DualDCMotor::driveStraight(){
  if(millis()-lastTime>=100){
    
  PWM = pidDrive.calc(setDis,analogRead(MaxBotixPin));
  if(prevPWM != PWM){
    analogWrite(leftMotor,PWM);
    analogWrite(rightMotor,PWM);
  }
  
  sideError = rightULS.Range() - setDis;
  if(sideError > 0){
    analogWrite(rightMotor,PWM-sideError);
  }
  else if(sideError < 0){
    analogWrite(leftMotor,PWM+sideError);
  }
  
  //Calculates the dutycycle of the PWM 0-1
//  PWM = analogWriteVal/255;

 //Sets the lastTime variable 
  lastTime=millis();
}
}



