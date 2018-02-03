int convertToServo(int value) {
  int minValue = 0;           // volts
  int maxValue = 3.3;
  int ratio = value / (maxValue - minValue);
  return (ratio * (maxServoRange - minServoRange)) + minServoRange;
}

void updateTimeAndVals() {
  prevTiltServoVal = tiltServoVal;
  timeAtChange = millis();
}

