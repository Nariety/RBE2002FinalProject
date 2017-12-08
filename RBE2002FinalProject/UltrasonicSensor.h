#include "Arduino.h"

#define meterPerSecond 29.1

class UltrasonicSensor{
  public:
  UltrasonicSensor(int trigPin, int echoPin);
  void setup();
  long Range();
  
  private:
  int trigPin;
  int echoPin;
};

