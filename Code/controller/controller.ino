#include "Servo.h"
#include "AnalogSmoothInt.h"
#include "ParkingLock.h"
#include <WheelSpeed.h>

/*pins*/
const int batteryPin = A5;    // Battery voltage divided down by 10
const int brakePin1 = A0;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int brakePin2 = A1;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int tiltPin = A2;       // Tilt lever input: ranges from the same values as potpin
const int brakePWMPin1 = 5;   // Output to the brake servo for one wheel
const int brakePWMPin2 = 6;   // Output to the brake servo for the second wheel 
const int tiltPWMPin = 7;     // Output to the tilt lock servo

/*battery*/
const int batteryVoltageCutoff = 3.6*4/3.3*1023/10;  // 
int batteryVoltage;
bool batteryGood;

/*LEVERS AND SERVOS variables*/
float brakeRead1;                     // value read in from brake lever after being smoothed
float tiltRead;                             // value read in from tilt lever after being smoothed
const int minValue = 2.380 * 1023/3.3;      //1.1V to 1.2V or 2.38V to 2.93V depending on potentiometer position
const int maxValue = 2.930 * 1023/3.3;
const int minHighTime = 800;                //min High time for PWM to servo, according to specs
const int maxHighTime = 2200;               //max High time for PWM to servo, according to specs
const int minServoRange = 100;              //0 degrees would output minHighTime
const int maxServoRange = 175;              //180 degrees would ouput maxHighTime
int brakeServoOutputProcessed1;             // after processed for locking
int tiltServoOutputProcessed;               // after processed for locking
int brakeServoOutput1;                      // servo output for brake
int tiltServoOutput;                        // servo output for tiltlock
/*For smoothing break input*/
AnalogSmoothInt smoothedBrake1 = AnalogSmoothInt(5);
AnalogSmoothInt smoothedTilt = AnalogSmoothInt(5);
/*For analyiing input for parking lock*/
const int periodBrakeRead = 10;             //period of brake input interrupt reading in ms
boolean leverReadTicked = 0;                //keep track of whether brake was read
const int lockingTime = 3000;               //ms until levers lock
const int lockingTol = 9;                   //tolerance for lever values to lock
ParkingLock brakeLock1 = ParkingLock(1000/periodBrakeRead,lockingTime, lockingTol);
ParkingLock tiltLock = ParkingLock(1000/periodBrakeRead,lockingTime, lockingTol);
/*Servo Objects*/
Servo brakeServo1;
Servo tiltServo;

/*WHEEL SPEED*/
int periodWheelRead = 2;
bool wheelReadTicked = false;

void setup() {  
  brakeServo1.attach(brakePWMPin1,minHighTime,maxHighTime);
  tiltServo.attach(tiltPWMPin,minHighTime,maxHighTime);  
  
  Serial.begin(9600);
  Serial.println("-- initialized --");
  Serial.println();
}

void loop() {
  checkBat(); //checks battery voltage and sets batteryGood
  
  /*This loop is entered once every 'periodBrakeRead' milliseconds, given that the rest of the program doesn't take too long*/
  if (!(millis()%periodBrakeRead) && !leverReadTicked && batteryGood) {         
    /*brake 1*/
    brakeRead1 = smoothedBrake1.analogReadSmooth(brakePin1);
    brakeServoOutput1 = convertToServo(brakeRead1);
    brakeServoOutputProcessed1 = brakeLock1.processParkingLock(brakeServoOutput1);
    brakeServo1.write(brakeServoOutputProcessed1); 
    /*tilt*/
    tiltRead = smoothedTilt.analogReadSmooth(tiltPin);
    tiltServoOutput = convertToServo(tiltRead);
    tiltServoOutputProcessed = tiltLock.processParkingLock(tiltServoOutput);
    tiltServo.write(tiltServoOutputProcessed); 

    leverReadTicked = 1;    
    Serial.print(brakeServoOutput1); Serial.print("\t");
    Serial.print(brakeServoOutputProcessed1); Serial.print("\t");
    Serial.println();
  } else if (millis()%periodBrakeRead) {
    leverReadTicked = 0;
  }

  if (!(millis()&periodWheelRead) && !wheelReadTicked) {
    
  }
  
}
