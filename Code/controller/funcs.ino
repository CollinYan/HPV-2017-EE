int convertToServo(double value) {
  double minValue = 600;           // volts
  double maxValue = 1024;
  double ratio = (value - minValue) / (maxValue - minValue);
  return (ratio * (maxServoRange - minServoRange)) + minServoRange;
}

void updateTimeAndVals() {
  prevTiltServoVal = tiltServoVal;
  timeAtChange = millis();
}

