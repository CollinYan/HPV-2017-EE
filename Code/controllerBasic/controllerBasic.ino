#include "Servo.h"
#include "AnalogSmoothInt.h"
#include "ParkingLock.h"

// Comment the following statement to disable logging on serial port.
#define SERIAL_PORT_LOG_ENABLE 1

/*pins*/
const int batteryPin = A4;    // Battery voltage divided down by 10
const int brakePin1 = A0;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int brakePin2 = A1;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int brakePin3 = A2;
const int tiltPin = A3;       // Tilt lever input: ranges from the same values as potpin
const int brakePWMPin1 = 9;   // Output to the brake servo for front wheel
const int brakePWMPin2 = 10;   // Output to the brake servo for rear left wheel 
const int brakePWMPin3 = 11;   // Output to the brake servo for rear right wheel 
const int tiltPWMPin = 12;     // Output to the tilt lock servo

/*Timing*/
const int periodBrakeRead = 10;             //period of brake input interrupt reading in ms
boolean leverReadTicked = 0;                //keep track of whether brake was read
const int periodServoWrite = 50;
boolean servoWriteTicked = 0;                //keep track of whether brake was read

/*battery*/
const int batteryVoltageCutoff = 3.6*4/3.3*1023/10;  // 
int batteryVoltage;
bool batteryGood;

/*LEVERS AND SERVOS variables*/
const int minValue = 2.380 * 1023/3.3;      //1.1V to 1.2V or 2.38V to 2.93V depending on potentiometer position
const int maxValue = 2.930 * 1023/3.3;
const int minHighTime = 800;                //min High time for PWM to servo, according to specs
const int maxHighTime = 2200;               //max High time for PWM to servo, according to specs
const int minServoRange = 100;              //0 degrees would output minHighTime
const int maxServoRange = 175;              //180 degrees would ouput maxHighTime
float brakeRead1;                     // value read in from brake lever after being smoothed
float tiltRead;                             // value read in from tilt lever after being smoothed
int brakeServoOutput1;                      // servo output for brake
int tiltServoOutput;                        // servo output for tiltlock
int brakeServoOutputProcessed1;             // after processed for locking
int tiltServoOutputProcessed;               // after processed for locking

/*For smoothing break input*/
AnalogSmoothInt smoothedBrake1 = AnalogSmoothInt(5);
AnalogSmoothInt smoothedTilt = AnalogSmoothInt(5);

/*Parking lock*/
const int lockingTime = 3000;               //ms until levers lock
const int lockingTol = 9;                   //tolerance for lever values to lock
ParkingLock brakeLock1 = ParkingLock(1000/periodBrakeRead,lockingTime, lockingTol);
ParkingLock tiltLock = ParkingLock(1000/periodBrakeRead,lockingTime, lockingTol);

/*Servo Objects*/
Servo brakeServo1;
Servo tiltServo;

void setup() {  
  brakeServo1.attach(brakePWMPin1,minHighTime,maxHighTime);
  tiltServo.attach(tiltPWMPin,minHighTime,maxHighTime);  
  
  Serial.begin(9600);
  Serial.println("-- initialized --");
  Serial.println();
}

void loop() {
  checkBat(); //checks battery voltage and sets batteryGood
  if (batteryGood) {
    readLever();  
    wheelSpeed();
    accelSpeed();
    brake();
  }
}
