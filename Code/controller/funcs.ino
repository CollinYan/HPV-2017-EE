int convertToServo(int value) {
  int minValue;                           // remember to set these based on voltage range
  int maxValue;
  int ratio = value / (maxValue - minValue);
  return (ratio * (maxServoRange - minServoRange)) + minServoRange;
}

void updateTimeAndVals() {
  prevServoVal = servoVal;
  timeAtChange = millis();
}

