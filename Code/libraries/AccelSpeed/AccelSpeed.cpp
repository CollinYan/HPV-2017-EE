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
    } else if (_brakeTime == 1) { //first time braking, calculate velocities based on _aixArr
      for (int i = 1; i <= (ARRA_SIZE+_arrayPos-_recentSyncIndice)%ARRA_SIZE; i++) { //loop from _recentSyncIndice+1 to _arrayPos
        _mphX100[_recentSyncIndice+i] = _mphX100[(_recentSyncIndice-1+ARRA_SIZE)%ARRA_SIZE]+(9.8*_aix * _scale / _freq) * 223.7;
      }
    } else if (_arrayPos>0) {
      //Serial.println("non-0 indicis");
      //Serial.println(_mphX100[_arrayPos-1]);
      //Serial.println((9.8*_aix * _scale / _freq) * 223.7);
      _mphX100[_arrayPos] = _mphX100[_arrayPos-1]+(9.8*_aix * _scale / _freq) * 223.7;  //  calculate mphX100 based on acceleration //HH: changed from a * (1/f) to a/f since 1/f=0
    } else if (_arrayPos == 0) {
      //Serial.println("indice 0");
      //Serial.println(_mphX100[_arrayPos-1]);
      //Serial.println((9.8*_aix * _scale / _freq) * 223.7);
      _mphX100[_arrayPos] = _mphX100[ARRA_SIZE-1]+(9.8*_aix * _scale / _freq) * 223.7;  //  calculate mphX100 based on acceleration //HH: changed from a * (1/f) to a/f since 1/f=0
    }
  }
  _interrupted = false;
  //Serial.print(_aix);
  //Serial.print("\t");
}
