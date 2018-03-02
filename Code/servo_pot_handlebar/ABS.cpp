#include "ABS.h"
#include "Arduino.h"

ABS::ABS(int kP, int kI, int kD, int maxSlip) {
  int _absBrakeOutput;
    int _slip;            // percent slip, should be around 5% to 20%
  
  private:
    int _absBrakeOutput;
}

void AccelSpeed::setAccel() {
  float aix, aiy, aiz;
  CurieIMU.readAccelerometerScaled(aix, aiy, aiz);
  _aix = aix;
  _interrupted = true;
}

void AccelSpeed::updateSpeed(int wheelSpeed, boolean braking) {
  if (!braking) {
    _vehicleSpeed = wheelSpeed;  // no brakes -> vehicles speed is same as wheels
    _vehicleDist = 0;
    _brakeTime = 0;
  }
  else if (braking) {
    _brakeTime += 1;
    if (_brakeTime > 65000) {  // braking time too long -> set vehicle speed to 0 //was 1000 set to 65000 for 65 sec
      _vehicleSpeed = 0;
    }
  }
  _vehicleSpeed += _aix / _freq;  //  calculate vehicleSpeed based on acceleration //HH: changed from a * (1/f) to a/f since 1/f=0
  _interrupted = false; 
}


