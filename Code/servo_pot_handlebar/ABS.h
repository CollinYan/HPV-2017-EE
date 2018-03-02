/*
  ABS.h - Library for calculating vehicle speed.
  Created by Harrison C. Hsueh, March 1 2018.
  Released into the public domain.
*/
#ifndef ABS_h
#define ABS_h
#include "Arduino.h"

class ABS {
  public:
    int ABS(int kP, int kI, int kD, int maxSlip);
    int processABS(int vehicleSpeedX10, int wheelSpeedX10, int desiredBrake);
    int _absBrakeOutput;
    int _slip;            // percent slip, should be around 5% to 20%
  
  private:
    int _absBrakeOutput;
};

#endif


