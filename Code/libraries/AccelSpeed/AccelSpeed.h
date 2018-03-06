/*
  Accelerometer.h - Library for calculating vehicle speed.
  Created by Harrison C. Hsueh, Keahooi Hung, November 12 2017.
  Released into the public domain.
*/
#ifndef AccelSpeed_h
#define AccelSpeed_h
#include "Arduino.h"

#define ARRA_SIZE 10

class AccelSpeed {
  public:
    AccelSpeed(int freq, float scale);
    void setAccel();         //HH: void since this function can just set the 'acceleration' variable for other functions to use
    volatile boolean _interrupted;      // set True when readAccel is called, set back to False after updating speed
    void updateSpeed(int wheelSpeed, int centerToCenter, boolean braking);  // function updating speed
    volatile float _aix;
    volatile float _aiy;
    volatile float _aiz;
    float _mphX100[ARRA_SIZE];
    float _aixArr[ARRA_SIZE];
    unsigned int _arrayPos;
    

  private:
    int _freq;
    int _brakeTime;
    float _scale;
    int _recentSyncIndice;
};

#endif
