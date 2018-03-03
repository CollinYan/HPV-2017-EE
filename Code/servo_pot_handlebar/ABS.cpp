#include "ABS.h"
#include "Arduino.h"

ABS::ABS(float kP, int kI, int kD, int maxSlip, int minBrake) {
  _maxSlip = constrain(maxSlip,0,20);
  _kP = kP;             //kP ~= 0.05  
  _slip = 0;            // percent slip, should be around 5% to 20%
  _absBrakeOutput = minBrake;
  _error = 0;
  _minBrake = minBrake;
}

int ABS::processABS(int vehicleSpeedX100, int wheelSpeedX100, int desiredBrake) {
  _slip = (vehicleSpeedX100 - wheelSpeedX100)*100/ vehicleSpeedX100;
  _error = _slip - _maxSlip;
  _absBrakeOutput -= kP*_error    //if brake at 180, and suddenly slips to 100%, then within 1 second, we want the braking to settly to 20%slip in 1second
  _absBrakeOutput = constrain(_absBrakeOutput,_minBrake, desiredBrake);
  return _absBrakeOutput;
}



