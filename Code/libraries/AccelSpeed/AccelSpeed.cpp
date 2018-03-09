#include "AccelSpeed.h"
#include "Arduino.h"
#include <CurieIMU.h>

AccelSpeed::AccelSpeed(int freq, float scale) {  // downscale read acceleration to compensate for tilted accelerometer
  CurieIMU.begin();                     // initialize curie
  CurieIMU.setAccelerometerRate(1600);    //HH: might need to increase this value to 100Hz

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(16);
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
  _freq = freq;                         //HH setting our private variable
  _scale = scale;
  _arrayPos = 0;
}

void AccelSpeed::setAccel() {
  float aix, aiy, aiz;
  CurieIMU.readAccelerometerScaled(aix, aiy, aiz);
  _aix = aix;
  _interrupted = true;
}

void AccelSpeed::updateSpeed(int wheelSpeed, int centerToCenter, boolean braking) {
  /*update _arrayPos*/
  _arrayPos = (_arrayPos + 1) % ARRA_SIZE;
 
  /*update _aixArr*/
  _aixArr[_arrayPos] = _aix;

  /*if not braking, sync wheel to older position*/
  if (!braking) {
    _recentSyncIndice = (_arrayPos-(centerToCenter/1000*_freq)/1000+ARRA_SIZE) % ARRA_SIZE; // microseconds/1000/1000*freq, add and mod to make sure non-negative
    _mphX100[_recentSyncIndice] = wheelSpeed;
    _brakeTime = 0;
  }
  else if (braking) {
    _brakeTime += 1;
    if (_brakeTime > 65000) {  // braking time too long -> set vehicle speed to 0 //was 1000 set to 65000 for 65 sec
      for (int i = 0; ARRA_SIZE; i++) {
        _mphX100[i] = wheelSpeed;
      }
    } else if (_brakeTime == 1) { //first time braking, calculate velocities based on last wheel sync and stored _aixArr
      for (int i = _recentSyncIndice; i < _recentSyncIndice+ARRA_SIZE-1; i++) {
      	_mphX100[(i+1)%ARRA_SIZE] = _mphX100[i%ARRA_SIZE] + 9.8 * _aixArr[(i+1)%ARRA_SIZE]*_scale/_freq*223.7;
      }
    } else {		//update speed at current time based off of _aix
      _mphX100[_arrayPos] = _mphX100[(_arrayPos+ARRA_SIZE-1)%ARRA_SIZE]+(9.8*_aix * _scale / _freq) * 223.7;  //  calculate mphX100 based on acceleration //HH: changed from a * (1/f) to a/f since 1/f=0
    }
  }
  _interrupted = false;
  //Serial.print(_aix);
  //Serial.print("\t");
}
