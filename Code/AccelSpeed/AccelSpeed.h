/*
  Accelerometer.h - Library for calculating vehicle speed.
  Created by Harrison C. Hsueh, Keahooi Hung, November 12 2017.
  Released into the public domain.
*/
#ifndef AccelSpeed_h
#define AccelSpeed_h
#include "Arduino.h"

class AccelSpeed {
  public:
    AccelSpeed(int freq);
    void setAccel();         //HH: void since this function can just set the 'acceleration' variable for other functions to use
    volatile boolean _interrupted;      // set True when readAccel is called, set back to False after updating speed
    void updateSpeed(int wheelSpeed, boolean braking);  // function updating speed
    float _mphX100;       // speed
    float _scale;
    volatile float _aix;
    volatile float _aiy;
    volatile float _aiz;

  private:
    int _freq;
    int _brakeTime;
};

#endif
