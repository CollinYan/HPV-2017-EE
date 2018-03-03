#include "AntiLockBrake.h"
#include "Arduino.h"

AntiLockBrake::AntiLockBrake(float kP, int kI, int kD, int maxSlip, int minBrake) {
  _maxSlip = constrain(maxSlip,0,20);
  _kP = kP;             //kP ~= 0.05  
  _slip = 0;            // percent slip, should be around 5% to 20%
  _absBrakeOutput = minBrake;
  _error = 0;
  _minBrake = minBrake;
}

int AntiLockBrake::processABS(int vehicleSpeedX100, int wheelSpeedX100, int desiredBrake) {
  if (vehicleSpeedX100 > 500) {
    _slip = (vehicleSpeedX100 - wheelSpeedX100)*100/ vehicleSpeedX100;
    _error = _slip - _maxSlip;
    _absBrakeOutput -= _kP*_error;    //if brake at 180, and suddenly slips to 100%, then within 1 second, we want the braking to settly to 20%slip in 1second
    _absBrakeOutput = constrain(_absBrakeOutput,_minBrake, desiredBrake);
  } else {
    _absBrakeOutput = desiredBrake;
  }
  return _absBrakeOutput;
}



