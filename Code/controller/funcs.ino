int convertToServo(double value) {
  double minValue = 0;           // volts
  double maxValue = 3.3;
  double ratio = value / (maxValue - minValue);
  return (ratio * (maxServoRange - minServoRange)) + minServoRange;
}

void updateTimeAndVals() {
  prevTiltServoVal = tiltServoVal;
  timeAtChange = millis();
}

