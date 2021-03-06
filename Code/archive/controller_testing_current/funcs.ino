int convertToServo(float brakeIn) {
  int angle;
  
  int p1 = minValue*10;
  int p2 = minValue*10 + (maxValue*10 - minValue*10)*0.1;
  int p3 = minValue*10 + (maxValue*10 - minValue*10)*0.5;
  int p4 = maxValue*10;

  int servoRange2 = minServoRange + (maxServoRange-minServoRange)*0.4;
  int servoRange3 = minServoRange + (maxServoRange-minServoRange)*0.75;
  
  if (brakeIn*10 < p2) {
    angle = map(brakeIn*10, p1, p2, minServoRange, servoRange2);
  } else if (brakeIn*10 < p3) {
    angle = map(brakeIn*10, p2+1, p3, servoRange2+1, servoRange3);
  } else {
    angle = map(brakeIn*10, p3+1, p4, servoRange3+1, maxServoRange);
  }
  
  angle = constrain(angle,minServoRange,maxServoRange);                               //protect servo in case voltage input goes outside of range
  return angle;
  
}

void updateTimeAndVals() {
  lockedTiltServoOutput = tiltServoOutput;
  timeAtChange = millis();
}

void processTiltServoOutput() {
  if (locked == true) {
    if (tiltServoOutput > minTiltServoOutput+ 20) {                                              //unlock
      locked = false;
      updateTimeAndVals();
      //Serial.println("unlocked");
    }
    else {                                                                                        //stay locked
      minTiltServoOutput = min(minTiltServoOutput, tiltServoOutput);
      tiltServoOutput = lockedTiltServoOutput;
      //Serial.println("staying locked");
    }
  }
  
  else if (locked != true) {
    if (lockedTiltServoOutput-9<tiltServoOutput && tiltServoOutput<lockedTiltServoOutput+9) {     //within lock range
      if (millis() - timeAtChange > 3000) {                                                       //within range long enough, lock
        locked = true;
        lockedTiltServoOutput = tiltServoOutput;
        minTiltServoOutput = lockedTiltServoOutput;
        //Serial.println("locked");
        //Serial.println("engaging lock");
      } 
      else {                                                                    
        tiltServoOutput = tiltServoOutput;                                                        //update but keep old time since within range
        //Serial.println("within range");
      }
    } 
    else {                                                                                        //not within range, just update                                  
      updateTimeAndVals(); 
      //Serial.println("not within range");
    }
  }
}

