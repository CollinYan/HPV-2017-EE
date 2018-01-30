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
    boolean accelRead();      // return interrupted
    void updateSpeed(int wheelSpeed, boolean braking);  // function updating speed
    volatile float vehicleSpeed;       // speed
    volatile float acceleration;       // acceleration value from arduino //HH making this public for testing
  
  private:
    int freq = freq;
    boolean interrupted;      // set True when readAccel is called, set back to False after updating speed
    int brake_time;           // not sure if we need this
};

#endif

