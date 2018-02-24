#include "AccelSpeed.h"
#include "CurieTimerOne.h"

const int timePeriod = 10000;               // frequency that timer will update (1000 microseconds = .001 sec) //Hchaged to 10ms for now
AccelSpeed myAccelSpeed(100);         // create AccelSpeed object with some frequency //change to 100Hz

int resetPeriod = 10;     // reset period in seconds
int resetDuration = 1;    // reset duration in seconds
boolean braking = true;

void timedUpdateSpeedISR() {
  myAccelSpeed.setAccel();
}

void setup() {
  CurieTimerOne.start(timePeriod, &timedUpdateSpeedISR);  // will run timedUpdateSpeed interrupt every .01 seconds
  Serial.begin(9600);                                     //debugging with Serial prints
}

void loop() {
  //Serial.print("velocity: ");
  Serial.print(myAccelSpeed._vehicleSpeed);
  Serial.print("\t");
  //Serial.print("accel: ");
  Serial.println(myAccelSpeed._aix);
  
  if (myAccelSpeed._interrupted) {
    myAccelSpeed.updateSpeed(0, braking);    // placeholders for wheelspeed and braking
  }
  
  if ((millis()/(1000*resetDuration))%(resetPeriod/resetDuration)==0) {
    braking = false;
  }
  else {
    braking = true;
  }
}

