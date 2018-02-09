int convertToServo(double brakeIn) {

  int angle = map(brakeIn, minValue, maxValue, minServoRange, maxServoRange); //maps brakeInput to servo angle
  angle = constrain(angle,minServoRange,maxServoRange);                               //protect servo in case voltage input goes outside of range
  return angle;
  
}

void updateTimeAndVals() {
  lockedTiltServoOutput = tiltServoOutput;
  timeAtChange = millis();
}

void processTiltServoOutput() {
  if (locked == true) {
    if (tiltServoOutput > lockedTiltServoOutput + 4) {                                            //unlock
      locked = false;
      updateTimeAndVals();
      Serial.println("unlocked");
    }
    else {                                                                                        //stay locked
      tiltServoOutput = lockedTiltServoOutput;
    }
  }
  
  else if (locked != true) {
    if (lockedTiltServoOutput-2<tiltServoOutput && tiltServoOutput<lockedTiltServoOutput+2) {     //within lock range
      if (millis() - timeAtChange > 3000) {                                                       //within range long enough, lock
        locked = true;
        tiltServoOutput = lockedTiltServoOutput;
        Serial.println("locked");
      } 
      else {                                                                    
        tiltServoOutput = tiltServoOutput;                                                        //update but keep old time since within range
      }
    } 
    else {                                                                                        //not within range, just update                                  
      updateTimeAndVals(); 
    }
  }
}

