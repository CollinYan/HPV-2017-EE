/*continuous*/
void accelSpeed() {  
  if (myAccelSpeed._interrupted) {
    myAccelSpeed.updateSpeed(wheel2._mphX10, braking);    // get wheelspeed from wheel 2
  }
  
  //Serial.print("accel's vehicle speed: ");

  //Serial.print("accel: ");
  //Serial.println(myAccelSpeed._aix);
  
  if ((millis() / (1000*resetDuration)) % (resetPeriod/resetDuration) == 0) {
    braking = false;
  }
  else {
    braking = true;
  }
}

/*100Hz*/

void timedUpdateSpeedISR() {
  myAccelSpeed.setAccel();
}



