#include "AccelSpeed.h"
#include "CurieTimerOne.h"

unsigned long start_time = 0;
unsigned long end_time = 0;

const int timePeriod = 10000;               // frequency that timer will update (1000 microseconds = .001 sec) //Hchaged to 10ms for now
AccelSpeed myAccelSpeed(100, 0.9);         // create AccelSpeed object with some frequency //change to 100Hz

int resetPeriod = 10;     // reset period in seconds
int resetDuration = 1;    // reset duration in seconds
boolean braking = true;

void timedUpdateSpeedISR() {
  myAccelSpeed.setAccel();
}

void setup() {
  
  CurieTimerOne.start(timePeriod, &timedUpdateSpeedISR);  // will run timedUpdateSpeed interrupt every .01 seconds
  Serial.begin(9600);
}

void loop() {
  Serial.print("velocity: ");
  Serial.print((myAccelSpeed._mphX100[2]));
  Serial.print("\t");
  //Serial.print("accel: ");
  //Serial.println(myAccelSpeed._aix);
  
  if (myAccelSpeed._interrupted) {
    myAccelSpeed.updateSpeed(0,0, braking);    // placeholders for wheelspeed and braking
  }
  Serial.println("crash9");
  
  if ((millis()/(1000*resetDuration))%(resetPeriod/resetDuration)==0) {
    Serial.println("@@@@@@@");
    braking = false;
  }
  else {
    Serial.println("crash11");
    braking = true;
  }
}


