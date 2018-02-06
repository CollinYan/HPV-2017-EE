int convertToServo(double value) {
  double minValue = 600;                                                  // 0-3.3V converted to 0-1024
  double maxValue = 1024;
  double ratio = (value - minValue) / (maxValue - minValue);
  int angle = (ratio * (maxServoRange - minServoRange)) + minServoRange;
  constrain(angle,minServoRange,maxServoRange);                           //protect servo in case voltage input goes outside of range
  return angle;
}

void updateTimeAndVals() {
  prevTiltServoVal = tiltServoVal;
  timeAtChange = millis();
}

