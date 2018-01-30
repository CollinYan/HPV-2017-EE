int convertTiltOutput(bool value) {
  if (value) {
    return maxServoRange;
  }
  return minServoRange;
}

int convertBrakeOutput(int value) {
  int minValue;
  int maxValue;
  int ratio = value / (maxValue - minValue);
  return (ratio * (maxServoRange - minServoRange)) + minServoRange;
}

