#include <WheelSpeed.h>
#include <Wire.h>

const int16_t frontSensorPin = 12;                    //digitalRead pin
const int16_t rearSensorPin = 13;                     //digitalRead pin
int frontRollout = 2136;                              //circumference of front wheel in mm
int rearRollout = 2136;                               //circumference of rear wheel in mm
int frontMag = 8;                                     //# of magnets on front wheel
int rearMag = 8;                                      //# of magnets on front wheel
int minSpeed = 4;                                     //minSpeed in mph
int freq = 4e3;                                       //need to set this value in setup() for Timer2
const int maxSpeed = 60;                              //normalize integer speed values sent over I2C to maxSpeed(mph)

/* maxTime in ms //minSpeed = frontRollout/frontMag / frontMaxTime * 1e-6km/mm / (1.6km/mi) * 3600s/h
 * frontMaxTime = frontRollout/frontMag * 1e-6km/mm / (1.6km/mi) * 3600s/h / minSpeed * 1000ms/s
 * MaxTime ( 2136mm, 8magnets, 2mph) ~= 0.3s = 300ms 
 * MaxTime ( 2136mm, 8magnets, 4mph) ~= 0.15s = 150ms 
 */
int frontMaxTime = (float)frontRollout/frontMag*1e-6 / 1.6 * 3600 / minSpeed * 1000; 
int rearMaxTime = (float)frontMaxTime*frontMag/rearMag;                              
                                    
volatile WheelSpeed frontWheel(frontSensorPin, frontRollout, frontMag, frontMaxTime, freq);
volatile WheelSpeed rearWheel(rearSensorPin, rearRollout, rearMag, rearMaxTime, freq); 

int rearSpeed1024;
int frontSpeed1024;
volatile int frontRearSpeed[2];
volatile uint16_t interruptCount = 0;

void setup() {
  Serial.begin(9600);                               //DEBUG ONLY
  Serial.println(frontMaxTime);
  Serial.println(rearMaxTime);
  setupTimer2();

  

  //Start I2C communication with master
  Wire.begin(8);                                      // join i2c bus with address #8
  Wire.onRequest(requestEvent);                       // register event`
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
  if (frontWheel.sensorRead()) {
    frontWheel.updateSpeed();
    frontSpeed1024 = 1024*frontWheel.mph / maxSpeed;    //Convert mph(float) to an integer, normalized to maxSpeed
    frontRearSpeed[0] = frontSpeed1024;                 //Set Data
  }
  if (rearWheel.sensorRead()) {
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
