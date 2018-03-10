void accelSpeed() { 
  /*100Hz*/
  //if (!((millis()*2/periodAccelRead)%2) && !accelReadTicked) {  //enters loop once every periodAccelRead        
  if (millis()-lastAccelRead > periodAccelRead) {
    myAccelSpeed.setAccel();
    lastAccelRead = millis(); 
    Serial.print(wheel2._mphX100);                            Serial.print("\t");
    Serial.print(wheel1._mphX100);                            Serial.print("\t");
    Serial.print((int)(myAccelSpeed._mphX100[accelIndice]));  Serial.print("\t");
    Serial.print(braking);                                    Serial.print("\t");
    Serial.println();  
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


