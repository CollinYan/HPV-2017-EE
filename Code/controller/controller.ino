#include "Servo.h"
#include "AnalogSmoothInt.h"
const int brakePin1 = A0;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int brakePin2 = A1;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int tiltPin = A2;       // Tilt lever input: ranges from the same values as potpin
const int brakePWMPin1 = 5;   // Output to the brake servo for one wheel
const int brakePWMPin2 = 6;   // Output to the brake servo for the second wheel 
const int tiltPWMPin = 7;      // Output to the tilt lock servo

float brakeRead1;    // value read in from brake lever
float tiltRead;   // value read in from tilt lever

bool locked = false;                  // True if tilt lever is held in same position for 3 seconds = 3000 ms
unsigned long timeAtChange = 0;       // Time at which the brake lever position last changed
int minTiltServoOutput = 0;
int lockedTiltServoOutput = 0;                    // Locked tilt lock value

int tiltServoOutput;                  // servo output for tiltlock
int brakeServoOutput;                 // servo output for brake

int minValue = 1.100 * 1023/3.3;                                                      // 0-3.3V converted to 0-1023
int maxValue = 1.200 * 1023/3.3;
int minServoRange = 70;
int maxServoRange = 170;

Servo brakeServo1;
Servo tiltServo;

/*for smoothing break input*/
AnalogSmoothInt smoothedBrake1 = AnalogSmoothInt(5);

boolean leverReadTicked = 0;

void setup() {  
  brakeServo1.attach(brakePWMPin1,800,2200); //sets 1000us and 2000us as 0degrees and 180degrees
  tiltServo.attach(tiltPWMPin);  
  
  Serial.begin(9600);
  Serial.println("-- initialized --");
  Serial.println();
}

void loop() {
  //200Hz brake lever reading
  if (!(millis()%5) && !leverReadTicked) {
    /*brake 1*/
    brakeRead1 = smoothedBrake1.analogReadSmooth(brakePin1);
    brakeServoOutput = convertToServo(brakeRead1);
    //brakeServo1.write(brakeServoOutput); 

    /*tilt*/
    tiltRead = analogRead(tiltPin);
    tiltServoOutput = convertToServo(tiltRead);
    tiltServoOutput = brakeServoOutput;
    Serial.print(tiltServoOutput);
    Serial.println();
    processTiltServoOutput();
    brakeServo1.write(tiltServoOutput); 
    tiltServo.write(tiltServoOutput); 
    
    leverReadTicked = 1;

    if (!millis()%500) {
      //Serial.print("tiltServoOutput: ");
      //Serial.println(tiltServoOutput);
      Serial.print("brakeServoOutput: ");
      Serial.print(brakeServoOutput);
      Serial.print("\t");
      Serial.print("brakeRead1: ");
      Serial.print(brakeRead1);
      Serial.print("\t");
      Serial.print("tiltRead: ");
      Serial.print(tiltRead);
      Serial.print("\t");
      Serial.println();
    }
  } else if (millis()%10) {
    leverReadTicked = 0;
  }

  delay(1);
}
