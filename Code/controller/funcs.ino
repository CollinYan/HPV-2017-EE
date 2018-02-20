int convertToServo(float brakeIn) {
  int angle;
  /*braking up input into 4 regions*/
  int p1 = minValue*10;
  int p2 = minValue*10 + (maxValue*10 - minValue*10)*0.1;
  int p3 = minValue*10 + (maxValue*10 - minValue*10)*0.5;
  int p4 = maxValue*10;
  /*Breaking up output into 4 regions*/
  int servoRange2 = minServoRange + (maxServoRange-minServoRange)*0.4;
  int servoRange3 = minServoRange + (maxServoRange-minServoRange)*0.75;
  
  if (brakeIn*10 < p2) {
    angle = map(brakeIn*10, p1, p2, minServoRange, servoRange2);
  } else if (brakeIn*10 < p3) {
    angle = map(brakeIn*10, p2+1, p3, servoRange2+1, servoRange3);
  } else {
    angle = map(brakeIn*10, p3+1, p4, servoRange3+1, maxServoRange);
  }  
  angle = constrain(angle,minServoRange,maxServoRange);                     //protect servo in case voltage input goes outside of range
  return angle;
}

void checkBat(){
  batteryVoltage = analogRead(batteryPin);
  batteryGood = batteryVoltage>batteryVoltageCutoff;
  //Serial.print(batteryVoltage*3.3*10/1023);
  //Serial.print("\t");
}
  
