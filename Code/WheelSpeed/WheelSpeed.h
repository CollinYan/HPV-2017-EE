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
  WheelSpeed(int tireRollout, int numMagnets, int minSpeed);
  void readTimeUp();            // reads the sensor value, only thing called in interrupt
  float updateSpeed();          // updates speed variable
  volatile bool _interruptedUp;             // variable for program to know whether speed needs updating
  float _mph;                    // speed in mph
  int _numPulses;                // for debugging
  
  private:
  /*miles per magnet times microseconds per hour, also mph*microsecond/magnet
    when divided by microseconds/magnet aka the time between pulses, the result is mph*/
  float _milesPerMagnetMicrosecondsPerHour; 
  int _centerToCenter;

  volatile int _tUp1;
  volatile int _tUp2;                     // time of rising edge of 2nd pulse
  int _recent;                   // time of most recent interrupt
  int _maxTime;                // max time between rising edges
  void calcSpeed();
};

#endif
