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
  void readSensor();            // reads the sensor value, only thing called in interrupt
  bool interrupted;             // variable for program to know whether speed needs updating
  float updateSpeed();          // updates speed variable
  float mph;                    // speed in mph
  int numPulses;                // for debugging
  String debug;                 // for debuggin
  int _reedValCur;               // current sensor val
  
  private:
  int _sensorPin;               // the number of the sensor pin
  float _rollout;               // the rollout of the wheel in millimeters; 2136mm for 28-622 tire; 1490mm for 40-406 tires;
  int _freq;                    // polling freq for sensor value

  int _debounceTimeC;           // time allowed for bouncing at edges in 100microseconds
  int _tDown1;                   // time of falling edge of 1st pulse
  int _tUp2;                     // time of rising edge of 2nd pulse
  int _tDown2;                   // time of falling edge of 2nd pulse
  int _timer;                   // time since last rising edge in 100microseconds
  int _maxTimeC;                // max cycles between rising edges
  int _magnets;                 // number of equally spaced magnets on the wheel
  volatile int _reedValOld;      // the previous reed position
};

#endif
