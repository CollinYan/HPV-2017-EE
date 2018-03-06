void accelSpeed() { 
  /*100Hz*/
  if (!((millis()*2/periodAccelRead)%2) && !accelReadTicked) {  //enters loop once every periodAccelRead        
     myAccelSpeed.setAccel();
     accelReadTicked = true;
  } else if ((millis()*2/periodAccelRead)%2) {
     accelReadTicked = false;
  }

  /*continuous*/
  braking = brakeServoOutput1 > (minServoRange+10);       //if lever is pressed enough, 10 out of approximately 90degrees of servo range
  if (myAccelSpeed._interrupted) {
    myAccelSpeed.updateSpeed(wheel2._mphX100, wheel2._centerToCenter, braking);    // get wheelspeed from wheel 2
  }
  
  /*  
  if ((millis() / (1000*resetDuration)) % (resetPeriod/resetDuration) == 0) {
    braking = false;
  } else {
    braking = true;
  }*/
}


