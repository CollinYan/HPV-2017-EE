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
  _tUpStore = 0;

  _interruptedUp = false;
  _mph = 0;
  _numPulses=0;

  _milesPerMagnetMicrosecondsPerHour = (float) tireRollout / 1e6 / 1.60934 / numMagnets * 1e6 * 60 * 60;
  _maxTime = _milesPerMagnetMicrosecondsPerHour / minSpeed;
  _centerToCenter = 0;
  _minTime = 2000;
}

void WheelSpeed::readTimeUp() {
  _tUp1 = _tUp2;
  _tUpStore = micros();
  _interruptedUp = true;
}


float WheelSpeed::updateSpeed() {
  //update speed of this wheel
  if (_interruptedUp) {
    if (_tUpStore - _tUp2 < _minTime) {
      _tUp2 = _tUp1;
    } else {
      _recent = _tUpStore;
      _tUp1 = _tUp2;
      _tUp2 = _tUpStore;
      calcSpeed();
      _numPulses += 1;
    }
    _interruptedUp = false;  
  }
  return _mph;
}

bool WheelSpeed::zeroMPH() {
  if (micros()-_recent > _maxTime) {
    _mph = 0;
    return true;
  }
  return false;
}

void WheelSpeed::calcSpeed() {
  _centerToCenter = _tUp2 - _tUp1;
  _mph = _milesPerMagnetMicrosecondsPerHour / _centerToCenter;
}

