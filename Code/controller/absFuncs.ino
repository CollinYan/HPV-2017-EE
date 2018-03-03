/*called by brake which is 10Hz*/
void antiLockBrake() {
  //antiLockBrake(myAccelSpeed._vehicleSpeedX10, wheel2._mphX10, 100, 100);
  absOutputWheel1 = absWheel1.processABS(myAccelSpeed._vehicleSpeed*22.4, wheel2._mphX10, brakeServoOutputProcessed1);
  absOutputWheel2 = absWheel2.processABS(myAccelSpeed._vehicleSpeed*22.4, wheel2._mphX10, brakeServoOutput2);
}

