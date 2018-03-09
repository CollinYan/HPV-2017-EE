/*called by brake which is 10Hz*/
void antiLockBrake() {
  int msTick = wheel2._centerToCenter/1000;
  accelIndice = myAccelSpeed._arrayPos-msTick/(1000/freq);
  if (accelIndice < 0) {
    accelIndice += 10;
  }
  if (1) {
  //if (myAccelSpeed._mphX100[accelIndice] < (minSpeed*1.5)*100 || !braking) {
    wheel1PID.SetMode(MANUAL);
    latestInput1 = brakeServoOutputProcessed1;
  } else {
    wheel1PID.SetMode(AUTOMATIC);
    //slip2 = (myAccelSpeed._mphX100[accelIndice] - wheel2._mphX100)/myAccelSpeed._mphX100[accelIndice]*10000;
    slip2 = (float)(wheel1._mphX100 - wheel2._mphX100)/wheel1._mphX100*10000;
  }
  Serial.print(wheel2._mphX100);                            Serial.print("\t");
  Serial.print(wheel1._mphX100);                            Serial.print("\t");
  Serial.print((int)(myAccelSpeed._mphX100[accelIndice]));  Serial.print("\t");
  Serial.print(brakeServoOutput1);                          Serial.print("\t");
  Serial.print(latestInput1);                               Serial.print("\t");
  Serial.print(braking);                                    Serial.print("\t");
  Serial.print(slip2);                                      Serial.print("\t");
}

