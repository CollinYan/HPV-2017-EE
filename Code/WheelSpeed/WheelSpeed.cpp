/*
  WheelSpeed.cpp - Library for getting wheel speed from a reed swithc.
  Created by Harrison C. Hsueh, October 10, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "WheelSpeed.h"

WheelSpeed::WheelSpeed(int tireRollout, int numMagnets, int minSpeed) {
  _recent = 0;
  _tUp1 = 0;
  _tUp2 = 0;

  _interruptedUp = false;
  _mphX100 = 0;
  _numPulses=0;

  _milesPerMagnetMicrosecondsPerHour = (float) tireRollout / 1e6 / 1.60934 / numMagnets * 1e6 * 60 * 60;  // near max value for unsigned int, change Div10 to Divxx to not overflow if change this val
  _maxTime = _milesPerMagnetMicrosecondsPerHour / minSpeed * 10;
  _centerToCenter = 0;
  _minTime = 2000;
}

void WheelSpeed::readTimeUp() {
  _tUp2 = micros();
  _interruptedUp = true;
}


void WheelSpeed::updateSpeed() {
  //update speed of this wheel
  if (_interruptedUp && !(_tUp2 - _tUp1 < _minTime)) {
    _recent = _tUp2;
    //Serial.print(_tUp2-_tUp1); Serial.print("\t");
    //Serial.println("calcing");
    calcSpeed();
    _tUp1 = _tUp2;
    _numPulses += 1;
  } else {
    //Serial.print(_tUp2);

    //Serial.println("bouncing");
  }
  _interruptedUp = false;
}

bool WheelSpeed::zeroMPH() {
  if (micros()-_recent > _maxTime) {
    _mphX100 = 0;
    //Serial.println("zeroed");
    return true;
  }
  return false;
}

void WheelSpeed::calcSpeed() {
  _centerToCenter = (_tUp2 - _tUp1)/100; //in 10microseconds, so we get mphX100 instead of just mph
  //Serial.print(_centerToCenter);
  //Serial.println(_milesPerMagnetMicrosecondsPerHour);
  _mphX100 = _milesPerMagnetMicrosecondsPerHour / _centerToCenter;
}
