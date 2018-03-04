#include "AccelSpeed.h"
#include "Arduino.h"
#include <CurieIMU.h>

AccelSpeed::AccelSpeed(int freq, float scale) {  // downscale read acceleration to compensate for tilted accelerometer
  CurieIMU.begin();                     // initialize curie
  CurieIMU.setAccelerometerRate(1600);    //HH: might need to increase this value to 100Hz

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
  _mphX100 = 0;                     //HH temporary initialize to 0
  _freq = freq;                         //HH setting our private variable
  _scale = scale;
}

void AccelSpeed::setAccel() {
  float aix, aiy, aiz;
  CurieIMU.readAccelerometerScaled(aix, aiy, aiz);
  _aix = aix;
  _interrupted = true;
}

void AccelSpeed::updateSpeed(int wheelSpeed, boolean braking) {
  if (!braking) {
    _mphX100 = wheelSpeed;  // no brakes -> vehicles speed is same as wheels
    //
    _brakeTime = 0;
  }
  else if (braking) {
    _brakeTime += 1;
    if (_brakeTime > 65000) {  // braking time too long -> set vehicle speed to 0 //was 1000 set to 65000 for 65 sec
      _mphX100 = 0;
    }
  }
  // downscale acceleration, then convert from m/s to 100 mi / h
  _mphX100 += (9.8*_aix * _scale / _freq) * 223.7;  //  calculate mphX100 based on acceleration //HH: changed from a * (1/f) to a/f since 1/f=0
  _interrupted = false;
  //Serial.print(_aix);
  //Serial.print("\t");
  //Serial.println((int)(_mphX100*22.4));
}
