/*called by brake which is 10Hz*/
void antiLockBrake() {
  int msTick = wheel2._centerToCenter/1000;
  accelIndice = myAccelSpeed._arrayPos-msTick/(1000/freq);
  if (accelIndice < 0) {
    accelIndice += 10;
  }
  slip2 = (myAccelSpeed._mphX100[accelIndice] - wheel2._mphX100)/myAccelSpeed._mphX100[accelIndice]*10000;
  absOutputWheel1 = absWheel1.processABS(myAccelSpeed._mphX100[accelIndice], wheel2._mphX100, brakeServoOutputProcessed1);
  absOutputWheel2 = absWheel2.processABS(myAccelSpeed._mphX100[accelIndice], wheel2._mphX100, brakeServoOutput2);
  Serial.print(wheel2._mphX100);                            Serial.print("\t");
  Serial.print(wheel1._mphX100);                            Serial.print("\t");
  Serial.print((int)(myAccelSpeed._mphX100[accelIndice]));  Serial.print("\t");
  Serial.print(brakeServoOutput1);                          Serial.print("\t");
  Serial.print(latestInput1);                               Serial.print("\t");
  Serial.print(braking);                                    Serial.print("\t");
  Serial.println();
}

