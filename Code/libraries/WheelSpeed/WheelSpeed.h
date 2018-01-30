/*
  WheelSpeed.h - Library for wheel speed.
  Created by Harrison C. Hsueh, October 10, 2017.
  Released into the public domain.
*/
#ifndef WheelSpeed_h
#define WheelSpeed_h

#include "Arduino.h"

class WheelSpeed {
  public:
  WheelSpeed(int pin, int tireRollout, int numMagnets, int maxTime, int freq);
  void readSensor();
  boolean sensorRead();
  float updateSpeed();
  float mph;
  int numPulses;
  String debug;
  int reedValCur;  
  
  private:
  int sensorPin;              // the number of the sensor pin
  float rollout;              // the rollout of the wheel in millimeters; 2136mm for 28-622 tire; 1490mm for 40-406 tires;
  int _freq;                  // polling freq for sensor value

  int _debounceTimeC;       // time allowed for bouncing at edges in 100microseconds
  int tDown1;                 // time of falling edge of 1st pulse
  int tUp2;                   // time of rising edge of 2nd pulse
  int tDown2;                 // time of falling edge of 2nd pulse
  int timer;                  // time since last rising edge in 100microseconds
  unsigned int _maxTimeC;              // max cycles between rising edges
  int _magnets;                // number of equally spaced magnets on the wheel
  volatile int reedValOld;             // the previous reed position
  
             // the current reed position
  volatile boolean interrupted;
};

#endif
