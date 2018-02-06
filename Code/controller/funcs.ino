int convertToServo(double brakeIn) {
  double minValue = 600;                                                      // 0-3.3V converted to 0-1023
  double maxValue = 1023;
  int angle = map(brakeIn, minValue, maxValue, minServoRange, maxServoRange); //maps brakeInput to servo angle
  constrain(angle,minServoRange,maxServoRange);                               //protect servo in case voltage input goes outside of range
  return angle;
  
}

void updateTimeAndVals() {
  prevTiltServoVal = tiltServoVal;
  timeAtChange = millis();
}

