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
  void readTimeUp();            // reads the sensor value, only thing called in interrupt
  void readTimeDown();            // reads the sensor value, only thing called in interrupt
  bool interrupted;             // variable for program to know whether speed needs updating
  float updateSpeed();          // updates speed variable
  float _mph;                    // speed in mph
  int numPulses;                // for debugging
  String debug;                 // for debuggin
  
  private:
  /*miles per magnet times microseconds per hour, also mph*microsecond/magnet
    when divided by microseconds/magnet aka the time between pulses, the result is mph*/
  int _milesPerMagnetMicrosecondsPerHour; 
  int _centerToCenter;

  int _tUp1;
  int _tDown1;                   // time of falling edge of 1st pulse
  int _tUp2;                     // time of rising edge of 2nd pulse
  int _tDown2;                   // time of falling edge of 2nd pulse
  int _recent;                   // time of most recent interrupt
  int _maxTimeC;                // max cycles between rising edges
  void calcSpeed();
  void updateCloseToOpen();
  void updateStuck();
  void updateOpenShort();
  void updateOpenToClose();
  void updateClosedShort();
};

#endif
