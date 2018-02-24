#include "AccelSpeed.h"
#include "Arduino.h"
#include <CurieIMU.h>
#include <MadgwickAHRS.h>

AccelSpeed::AccelSpeed(int freq) {
  CurieIMU.begin();                     // initialize curie
  CurieIMU.setAccelerometerRate(100);    //HH: might need to increase this value to 100Hz

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);

  _vehicleSpeed = 0;                     //HH temporary initialize to 0
  _freq = freq;                         //HH setting our private variable
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

