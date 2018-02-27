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
  _mphX10 = 0;
  _numPulses=0;

  _milesDiv100PerMagnetMicrosecondsPerHour = (float) tireRollout / 1e6 / 1.60934 / numMagnets * 1e6 * 60 * 60 / 100;
  _maxTime = _milesDiv100PerMagnetMicrosecondsPerHour / minSpeed;
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
    calcSpeed();
    _tUp1 = _tUp2;    
    _numPulses += 1;
  }
  _interruptedUp = false;  
}

bool WheelSpeed::zeroMPH() {
  if (micros()-_recent > _maxTime) {
    _mphX10 = 0;
    return true;
  }
  return false;
}

void WheelSpeed::calcSpeed() {
  _centerToCenter = _tUp2 - _tUp1;
  _mphX10 = _milesDiv100PerMagnetMicrosecondsPerHour / _centerToCenter;
}

