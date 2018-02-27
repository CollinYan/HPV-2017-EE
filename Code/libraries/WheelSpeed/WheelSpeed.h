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
  bool zeroMPH();               // checks if last magnet pass was greater than _maxTime
  volatile bool _interruptedUp;             // variable for program to know whether speed needs updating
  float _mph;                    // speed in mph
  int _numPulses;                // for debugging
  int _maxTime;                // max time between rising edges
  
  private:
  /*miles per magnet times microseconds per hour, also mph*microsecond/magnet
    when divided by microseconds/magnet aka the time between pulses, the result is mph*/
  float _milesPerMagnetMicrosecondsPerHour; 
  int _centerToCenter;

  int _minTime;
  volatile int _tUp1;
  volatile int _tUp2;                     // time of rising edge of 2nd pulse
  volatile int _tUpStore;                 // time of recent interrupt, might be bouncing
  int _recent;                   // time of most recent interrupt
  
  void calcSpeed();
};

#endif
