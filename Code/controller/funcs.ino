int convertToServo(float brakeIn) {

  int angle = map(brakeIn*10, minValue*10, maxValue*10, minServoRange, maxServoRange); //maps brakeInput to servo angle
  angle = constrain(angle,minServoRange,maxServoRange);                               //protect servo in case voltage input goes outside of range
  return angle;
  
}

void updateTimeAndVals() {
  lockedTiltServoOutput = tiltServoOutput;
  timeAtChange = millis();
}

void processTiltServoOutput() {
  if (locked == true) {
    if (tiltServoOutput > minTiltServoOutput+ 20) {                                            //unlock
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
        tiltServoOutput = lockedTiltServoOutput;
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

