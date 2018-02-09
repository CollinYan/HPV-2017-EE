#include "Servo.h"
#include "AnalogSmooth.h"
const int brakePin1 = A0;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int brakePin2 = A1;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int tiltPin = A2;       // Tilt lever input: ranges from the same values as potpin
const int brakePWMPin1 = 5;   // Output to the brake servo for one wheel
const int brakePWMPin2 = 6;   // Output to the brake servo for the second wheel 
const int tiltPWMPin = 7;      // Output to the tilt lock servo

int brakeRead1;    // value read in from brake lever
int tiltRead;   // value read in from tilt lever

bool locked = false;                  // True if tilt lever is held in same position for 3 seconds = 3000 ms
int tiltServoVal;                     // pot read converted to tilt servo val
int prevTiltServoVal = 0;
unsigned long timeAtChange = 0;       // Time at which the brake lever position last changed
int lockedVal = 0;                    // Locked tilt lock value

int tiltServoOutput;                  // servo output for tiltlock
int brakeServoOutput;                 // servo output for brake

int minValue = 1.100 * 1023/3.3;                                                      // 0-3.3V converted to 0-1023
int maxValue = 1.200 * 1023/3.3;
int minServoRange = 70;
int maxServoRange = 170;

Servo brakeServo;
Servo tiltServo;

/*for smoothing break input*/
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {  
  brakeServo.attach(brakePWMPin1,800,2200); //sets 1000us and 2000us as 0degrees and 180degrees
  tiltServo.attach(tiltPWMPin);  
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  Serial.begin(9600);
  Serial.println("-- initialized --");
  Serial.println();
}

void loop() {
  brakeRead1 = analogRead(brakePin1);
  smooth();
  tiltRead = analogRead(tiltPin);
  if ( 0 ) {
      Serial.print("tiltRead: ");
      Serial.println(tiltRead);
        Serial.println("");
  }  
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

  //Serial.print("tiltServoOutput: ");
  //Serial.println(tiltServoOutput);
  Serial.print("brakeServoOutput: ");
  Serial.print(brakeServoOutput);
  Serial.print("\t");
  Serial.print(brakeRead1);
  Serial.println();
  
  brakeServo.write(brakeServoOutput); 
  tiltServo.write(tiltServoOutput); 
  delay(1);
}
