/*called by brake which is 10Hz*/
void antiLockBrake() {
  slip2 = (myAccelSpeed._mphX100[accelIndice] - wheel2._mphX100)/myAccelSpeed._mphX100[accelIndice]*10000;
  Serial.print(wheel2._mphX100);                            Serial.print("\t");
  Serial.print(wheel1._mphX100);                            Serial.print("\t");
  Serial.print((int)(myAccelSpeed._mphX100[accelIndice]));  Serial.print("\t");
  Serial.print(brakeServoOutput2);                          Serial.print("\t");
  Serial.print(latestInput2);                               Serial.print("\t");
  Serial.print(slip2);                                      Serial.print("\t");
  Serial.print(braking);                                    Serial.print("\t");
  Serial.println();
}

