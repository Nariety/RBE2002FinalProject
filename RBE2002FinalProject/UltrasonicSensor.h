#include "Arduino.h"

#define meterPerSecond 29.1

class UltrasonicSensor{
  public:
  UltrasonicSensor();
  void setup(int trigPin, int echoPin);
  long Range();
  
  private:
  int trigPin;
  int echoPin;
};

