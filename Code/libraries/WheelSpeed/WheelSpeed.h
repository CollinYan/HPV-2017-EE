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
  void updateSpeed();          // updates speed variable
  bool zeroMPH();               // checks if last magnet pass was greater than _maxTime
  volatile bool _interruptedUp;             // variable for program to know whether speed needs updating
  int _mphX10;                    // speed in mph
  uint8_t _numPulses;                // for debugging
  unsigned int _maxTime;                // max time between rising edges
  
  private:
  /*miles per magnet times microseconds per hour, also mph*microsecond/magnet
    when divided by microseconds/magnet aka the time between pulses, the result is mph*/
  unsigned int _milesDiv10PerMagnetMicrosecondsPerHour; 
  int _centerToCenter;

  int _minTime;
  volatile int _tUp1;
  volatile int _tUp2;                     // time of rising edge of 2nd pulse
  unsigned int _recent;                   // time of most recent interrupt
  
  void calcSpeed();
};

#endif
