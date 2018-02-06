#include "Servo.h"
const int brakePin1 = A0;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int brakePin2 = A1;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int tiltPin = A2;       // Tilt lever input: ranges from the same values as potpin
const int brakePWMPin1 = 5;   // Output to the brake servo for one wheel
const int brakePWMPin2 = 6;   // Output to the brake servo for the second wheel 
const int tilPWMPin = 7;      // Output to the tilt lock servo

int brakeRead1;    // value read in from brake lever
int tiltRead;   // value read in from tilt lever

bool locked = false;                  // True if tilt lever is held in same position for 3 seconds = 3000 ms
int tiltServoVal;                     // pot read converted to tilt servo val
int prevTiltServoVal = 0;
unsigned long timeAtChange = 0;       // Time at which the brake lever position last changed
int lockedVal = 0;                    // Locked tilt lock value

int tiltServoOutput;                  // servo output for tiltlock
int brakeServoOutput;                 // servo output for brake

int minServoRange = 0;
int maxServoRange = 180;

Servo brakeServo;

void setup() {  
  myservo.attach(brakePin1);  

  Serial.begin(9600);
  Serial.println("-- initialized --");
  Serial.println();
}

void loop() {
  brakeRead1 = analogRead(brakePin1);
  tiltRead = analogRead(tiltPin);
  Serial.print("tiltRead: ");
  Serial.println(tiltRead);
  Serial.println("");
  
  tiltServoVal = convertToServo(tiltRead);
  brakeServoOutput = convertToServo(brakeRead1);
  
  if (locked == true) {
    if (tiltServoVal > prevTiltServoVal + 4) {
      locked = false;
      tiltServoOutput = tiltServoVal;
      updateTimeAndVals();
      Serial.println("unlocked");
    }
    else {
      tiltServoOutput = lockedVal;
      // updateTimeAndVals();
    }
  }
  
  else if (locked != true) {
    if (tiltServoVal != prevTiltServoVal) {
      tiltServoOutput = tiltServoVal;
      updateTimeAndVals();
    } 
    else {
      if (millis() - timeAtChange > 3000) {  // dont update timeatchange
        locked = true;
        lockedVal = tiltServoVal;
        tiltServoOutput = tiltServoVal;
        Serial.println("locked");
      }
    }
  }

  Serial.print("tiltServoOutput: ");
  Serial.println(tiltServoOutput);
  
  brakeServo.write(brakeServoOutput); 
  delay(100);
}
