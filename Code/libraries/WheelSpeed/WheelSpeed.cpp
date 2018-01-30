/*
  WheelSpeed.cpp - Library for getting wheel speed from a reed swithc.
  Created by Harrison C. Hsueh, October 10, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "WheelSpeed.h"

WheelSpeed::WheelSpeed(int pin, int tireRollout, int numMagnets, int maxTime, int freq) {
  sensorPin = pin;
  pinMode(sensorPin, INPUT);
  rollout = tireRollout;
  _magnets = numMagnets;
  
  _freq = freq; 
  timer = 0;
  reedValOld = 0;
  reedValCur = 0;
  tDown1 = 0;                
  tUp2 = 0;
  tDown2 = 0;  
  _debounceTimeC = 1;                        // cycles allowed for bouncing at edges in time intervals of interrupt
  Serial.println( "calc mxatimec");
  _maxTimeC = (unsigned long) maxTime * _freq / 1000;      //max cycles between rising edge (maxTime(ms), _freq(Hz))
  Serial.println( "calced mxatimec");
  interrupted = false;
  mph = 0;
  numPulses=0;
}

void WheelSpeed::readSensor() {
  reedValCur = digitalRead(sensorPin);
  interrupted = 1;
}

boolean WheelSpeed::sensorRead() {
  return interrupted;
}

float WheelSpeed::updateSpeed() {
  //update speed of this wheel
  if (!reedValCur) {  //reed open
    if (reedValOld && timer-tUp2 > _debounceTimeC) { //went from closed to open and done bouncing
      tDown2 = timer;
      mph = (float)rollout / 1e6 / 1.60934 / _magnets / (float (tUp2 + tDown2 - tDown1) / 2) * _freq * 60 * 60; //1e3 = 1/ interrupt time in seconds
      //mph = float (tUp2 + tDown2 - tDown1) / 2;
      reedValOld = reedValCur;
      tDown1 = tDown2 - tUp2;                     //move most recent completed pulse falling edge's reference to its rising edge
      timer = tDown1;                             //move timer reference to rising edge of most recent completed pulse
      numPulses += 1;
      debug = String("went from closed to open and done bouncing");
      timer += 1;
    }
    else if (timer-tDown1 > _maxTimeC) { //open for greater than _maxTime
      mph = 0;
      debug = String("open for greater than _maxTime");
      debug += _maxTimeC;
    }
    else {
      timer += 1;
      debug = String("still bouncing after close or still open");
      //debug += timer;
    }
  }
  else {              //reed closed
    if (!reedValOld && timer-tDown1 > _debounceTimeC) { //went from open to closed and done bouncing
      tUp2 = timer;
      reedValOld = reedValCur;
      debug = String("went from open to closed and done bouncing");
      timer += 1;
    }
    else if (reedValOld && timer - tUp2 > _maxTimeC) { //closed for greater than _maxTime
      mph = 0;
      debug = String("closed for greater than _maxTime");
    }
    else {
      timer += 1;
      debug = String("still bouncing after open or still closed");
    }
  }
  interrupted = 0;
  return mph;
}

