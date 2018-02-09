int convertToServo(double brakeIn) {

  int angle = map(brakeIn, minValue, maxValue, minServoRange, maxServoRange); //maps brakeInput to servo angle
  angle = constrain(angle,minServoRange,maxServoRange);                               //protect servo in case voltage input goes outside of range
  return angle;
  
}

void updateTimeAndVals() {
  prevTiltServoVal = tiltServoVal;
  timeAtChange = millis();
}

void smooth() {
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = brakeRead1;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  brakeRead1 = average;
}

