#include "WheelSpeed.h"
#include "CurieTimerOne.h"

const int16_t wheel1Pin = 6;                    //digitalRead pin
const int16_t wheel2Pin = 7;                     //digitalRead pin
const int16_t wheel2Pin = 8;                     //digitalRead pin
const int frontRollout = 2136;                              //circumference of front wheel in mm
const int rearRollout = 2136;                               //circumference of rear wheel in mm
const int frontMag = 8;                                     //# of magnets on front wheel
const int rearMag = 8;                                      //# of magnets on front wheel
const int minSpeed = 5;                                     //minSpeed in mph
const int freq = 4e3;                                       //need to set this value in setup() for Timer2
int timePeriod = 10000;               // frequency that timer will update (1000 microseconds = .001 sec) //Hchaged to 10ms for now
const int maxSpeed = 60;                              //normalize integer speed values sent over I2C to maxSpeed(mph)

/* maxTime in ms //minSpeed = frontRollout/frontMag / frontMaxTime * 1e-6km/mm / (1.6km/mi) * 3600s/h
 * frontMaxTime = frontRollout/frontMag * 1e-6km/mm / (1.6km/mi) * 3600s/h / minSpeed * 1000ms/s
 * MaxTime ( 2136mm, 8magnets, 2mph) ~= 0.3s = 300ms 
 * MaxTime ( 2136mm, 8magnets, 4mph) ~= 0.15s = 150ms 
 */
int frontMaxTime = (float)frontRollout/frontMag*1e-6 / 1.6 * 3600 / minSpeed * 1000; 
int rearMaxTime = (float)frontMaxTime*frontMag/rearMag;                              
                                    
WheelSpeed frontWheel(frontSensorPin, frontRollout, frontMag, frontMaxTime, freq);
WheelSpeed rearWheel(rearSensorPin, rearRollout, rearMag, rearMaxTime, freq); 

int rearSpeed1024;
int frontSpeed1024;
volatile int frontRearSpeed[2];
volatile uint16_t interruptCount = 0;

void setup() {
  Serial.begin(9600);                               //DEBUG ONLY
  Serial.println(frontMaxTime);
  Serial.println(rearMaxTime);
  attachInterrupt(digitalPinToInterrupt(wheel1Pin), wheel1UpISR, RISING);
  attachInterrupt(digitalPinToInterrupt(wheel2Pin), wheel2UpISR, RISING);
  attachInterrupt(digitalPinToInterrupt(wheel3Pin), wheel3UpISR, RISING);
  attachInterrupt(digitalPinToInterrupt(wheel1Pin), wheel1DownISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(wheel2Pin), wheel2DownISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(wheel3Pin), wheel3DownISR, FALLING);
}

void loop() {
  if (interruptCount % 1 == 0) {
    /*
    Serial.print(frontWheel.mph);
    Serial.print("\t");
    Serial.print(rearWheel.mph);
    Serial.print("\t");
    Serial.print(frontWheel.reedValCur);
    Serial.print("\t");
    Serial.print(rearWheel.reedValCur);
    Serial.print("\t");
    
    Serial.print(interruptCount);
    Serial.print("\t");
    Serial.print(frontSpeed1024);
    Serial.print("\t");
    Serial.print(frontWheel.debug);
    Serial.print("\t");
    Serial.print(rearWheel.debug);
    Serial.println();
    */
  }
  if (frontWheel.interrupted) {
    frontWheel.updateSpeed();
    frontSpeed1024 = 1024*frontWheel.mph / maxSpeed;    //Convert mph(float) to an integer, normalized to maxSpeed
    frontRearSpeed[0] = frontSpeed1024;                 //Set Data
  }
  if (rearWheel.interrupted) {
    rearWheel.updateSpeed();
    rearSpeed1024 = 1024*rearWheel.mph / maxSpeed;
    frontRearSpeed[1] = rearSpeed1024;
  }

  if (millis() % 50 == 0) {
    Serial.print(interruptCount);
    Serial.print("\t");
    Serial.println(rearWheel.mph);                   //DEBEUG ONLY  
  }

}
