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
    int ABS(float kP, int kI, int kD, int maxSlip, int minBrake);
    int processABS(int vehicleSpeedX100, int wheelSpeedX100, int desiredBrake);
    int _slip;            // percent slip, should be around 5% to 20%
  
  private:
    float _kP;
    int _maxslip
    float _absBrakeOutput;
    int _error;
    int _minBrake;
    
};

#endif


