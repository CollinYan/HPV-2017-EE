/*
  WheelSpeed.cpp - Library for getting wheel speed from a reed swithc.
  Created by Harrison C. Hsueh, October 10, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "WheelSpeed.h"

WheelSpeed::WheelSpeed(int pin, int tireRollout, int numMagnets, int maxTime, int freq) {
  _sensorPin = pin;
  pinMode(_sensorPin, INPUT);
  _rollout = tireRollout;
  _magnets = numMagnets;
  
  _freq = freq; 
  _timer = 0;
  _reedValOld = 0;
  _reedValCur = 0;
  _tDown1 = 0;                
  _tUp2 = 0;
  _tDown2 = 0;  
  Serial.println( "calc mxatimec");
  _maxTimeC = (unsigned long) maxTime * _freq / 1000;      //max cycles between rising edge (maxTime(ms), _freq(Hz))
  Serial.println( "calced maxTimeC");
  interrupted = false;
  mph = 0;
  numPulses=0;
}

void WheelSpeed::readSensor() {
  _reedValCur = digitalRead(_sensorPin);
  interrupted = 1;
}

float WheelSpeed::updateSpeed() {
  //update speed of this wheel
  if (!_reedValCur) {                       //reed open
    if (_reedValOld) {                        //went from closed to open and done bouncing
      updateCloseToOpen();
    }
    else if (_timer-_tDown1 > _maxTimeC) {    //open for greater than _maxTime
      updateStuck();
    }
    else {                                    //open but waiting for close
      updateOpenShort();
    }
  }
  else {                                    //reed closed
    if (!_reedValOld) {                       //went from open to closed and done bouncing
      updateOpenToClose();
    }
    else if (_reedValOld && _timer - _tUp2 > _maxTimeC) { //closed for greater than _maxTime
      updateStuck();
    }
    else {
      updateClosedShort();
    }
  }
  interrupted = 0;
  return mph;
}

void WheelSpeed::updateCloseToOpen() {
  _tDown2 = _timer;
  mph = (float)_rollout / 1e6 / 1.60934 / _magnets / (float (_tUp2 + _tDown2 - _tDown1) / 2) * _freq * 60 * 60; //1e3 = 1/ interrupt time in seconds
  _reedValOld = _reedValCur;
  _tDown1 = _tDown2 - _tUp2;                     //move most recent completed pulse falling edge's reference to its rising edge
  _timer = _tDown1;                             //move _timer reference to rising edge of most recent completed pulse
  numPulses += 1;
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

