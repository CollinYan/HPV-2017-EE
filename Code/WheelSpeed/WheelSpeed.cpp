/*
  WheelSpeed.cpp - Library for getting wheel speed from a reed swithc.
  Created by Harrison C. Hsueh, October 10, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "WheelSpeed.h"

WheelSpeed::WheelSpeed(int tireRollout, int numMagnets, int maxTime, int freq) {  
  _timer = 0;
  _tDown1 = 0;                
  _tUp2 = 0;
  _tDown2 = 0;  
  Serial.println( "calc maxtimec");

  interrupted = false;
  _mph = 0;
  numPulses=0;
  
  _milesPerMagnetMicrosecondsPerHour = (float)_rollout / 1e6 / 1.60934 / _magnets * 1e6 * 60 * 60;
  _centerToCenter = 0;
}

void WheelSpeed::readTimeUp() {
  _tUp2 = micros();
  interruptedUp = true;
}
void WheelSpeed::readTimeDown() {
  _tDown2 = micros()
  interruptedDown = true;
}

float WheelSpeed::updateSpeed() {
  //update speed of this wheel
  if (interruptedDown) {
    calcSpeed();
    _tUp1 = _tUp2;
    _tDown1 = _tDown2;
    _recent = _tDown2;
    interruptedDown = false;
  } else if (interruptedUp) {
    _recent = _tUp2;
    interruptedUp = false;
  }
  if (micros()-_recent > _maxTime) {
    _mph = 0;
  }
  return mph;
}

void WheelSpeed::calcSpeed() {
  _centerToCenter = (_tUp2 - _tUp1 + _tDown2 - _tDown1) /2;
  mph = milesPerMagnetMicrosecondsPerHour / _centerToCenter;
  debug = String("went from closed to open and done bouncing");
  _timer += 1;
}

void WheelSpeed::updateStuck() {
  mph = 0;
  debug = String("open or close for greater than _maxTime");
  debug += _maxTimeC;
}

void WheelSpeed::updateOpenShort() {
  _timer += 1;
  debug = String("still open");
  //debug += _timer;
}

void WheelSpeed::updateOpenToClose() {
  _tUp2 = _timer;
  _reedValOld = _reedValCur;
  debug = String("went from open to closed and done bouncing");
  _timer += 1;
}

void WheelSpeed::updateClosedShort() {
  _timer += 1;
  debug = String("still closed");
}

