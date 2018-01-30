#include "AccelSpeed.h"
#include "Arduino.h"
#include <CurieIMU.h>
#include <MadgwickAHRS.h>

AccelSpeed::AccelSpeed(int _freq) {
  CurieIMU.begin();                     // initialize curie
  CurieIMU.setAccelerometerRate(100);    //HH: might need to increase this value to 100Hz

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);

  vehicleSpeed = 0;                     //HH temporary initialize to 0
  freq = _freq;                         //HH setting our private variable
}

void AccelSpeed::setAccel() {
  float aix, aiy, aiz;
  //int gix, giy, giz;
  //CurieIMU.readMotionSensor(aix, aiy, aiz, gix, giy, giz);  // get data from sensor
  CurieIMU.readAccelerometerScaled(aix, aiy, aiz);
  
  //acceleration = (aix * 2.0) / 32768.0;   // get and set x acceleration in range from -2g to 2g //HH: changed from 'accel' to 'acceleration'
  acceleration = aix;
  interrupted = true;
}

boolean AccelSpeed::accelRead() {
  return interrupted;
}

void AccelSpeed::updateSpeed(int wheelSpeed, boolean braking) {
  if (!braking) {
    vehicleSpeed = wheelSpeed;  // no brakes -> vehicles speed is same as wheels
    brake_time = 0;
  }
  else if (braking) {
    brake_time += 1;
    if (brake_time > 65000) {  // braking time too long -> set vehicle speed to 0 //was 1000 set to 65000 for 65 sec
      vehicleSpeed = 0;
    }
  }
  vehicleSpeed += acceleration / freq;  //  calculate vehicleSpeed based on acceleration //HH: changed from a * (1/f) to a/f since 1/f=0
  interrupted = false; 
}

