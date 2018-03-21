/*100Hz*/
void readLever() {
  /*This loop is entered once every 'periodBrakeRead' milliseconds, given that the rest of the program doesn't take too long*/
  if (!((millis()*2/periodBrakeRead)%2) && !leverReadTicked) {         
    /*brake 1-3*/
    brakeRead1 = smoothedBrake1.analogReadSmooth(brakePin1);
    brakeServoOutput1 = convertToServo(brakeRead1);
    if (wheel2._mphX100 < 200) {//dont lock if over 2mph
      brakeServoOutput1 = brakeLock1.processParkingLock(brakeServoOutput1);
    }
    brakeServoOutput2 = brakeServoOutput1;
    brakeServoOutput3 = brakeServoOutput1;
        
    /*tilt*/
    tiltRead = smoothedTilt.analogReadSmooth(tiltPin);
    tiltServoOutput = convertToServo(tiltRead);
    if (wheel2._mphX100 < 200) {//dont lock if over 2mph
      tiltServoOutput = brakeLock1.processParkingLock(tiltServoOutput);
    }

    leverReadTicked = true;      
    
  } else if ((millis()*2/periodBrakeRead)%2) {
    leverReadTicked = false;
  }
}

/*10Hz*/
void brake() {
  if (!((millis()*2/periodServoWrite)%2) && !servoWriteTicked) {        

    Serial.print(wheel2._mphX100);                            Serial.print("\t");
    Serial.print(wheel1._mphX100);                            Serial.print("\t");
    Serial.print(brakeServoOutput1);                          Serial.print("\t");
    Serial.println();  
    brakeServo1.write(brakeServoOutput1); 
    brakeServo2.write(brakeServoOutput2); 
    brakeServo3.write(brakeServoOutput3); 
    tiltServo.write(tiltServoOutput); 
    servoWriteTicked = true;
  } else if ((millis()*2/periodServoWrite)%2) {
    servoWriteTicked = false;
  }
}

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


  

