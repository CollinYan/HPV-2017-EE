#include "WheelSpeed.h"

unsigned long start_time = 0;
unsigned long end_time = 0;

const int16_t wheel1Pin = 6;                    //digitalRead pin
const int16_t wheel2Pin = 7;                     //digitalRead pin
const int16_t wheel3Pin = 8;                     //digitalRead pin
const int rollout1 = 2136;                              //circumference of front wheel in mm
const int rollout2 = 2136;                               //circumference of rear left wheel in mm
const int rollout3 = 2136;                               //circumference of rear right wheel in mm
const int magnets1 = 8;                                     //# of magnets on front wheel
const int magnets2 = 8;                                      //# of magnets on rear left wheel
const int magnets3 = 8;                                      //# of magnets on rear right wheel
const int minSpeed = 5;                                     //minSpeed in mph

WheelSpeed wheel1(rollout1, magnets1, minSpeed);
WheelSpeed wheel2(rollout2, magnets2, minSpeed); 
WheelSpeed wheel3(rollout2, magnets3, minSpeed); 

void setup() {
  Serial.begin(9600);                               //DEBUG ONLY
  Serial.println("serial started");
  attachInterrupt(digitalPinToInterrupt(wheel1Pin), wheel1UpISR, RISING);
  attachInterrupt(digitalPinToInterrupt(wheel2Pin), wheel2UpISR, RISING);
  attachInterrupt(digitalPinToInterrupt(wheel3Pin), wheel3UpISR, RISING);
}

void loop() {
  delay(2000);
  Serial.println("waited 2 secs");
  delay(2000);
  Serial.println("waited 2nd 2 secs");
  delay(2000);
  Serial.println("waited 3nd 2 secs");
  delay(2000);
  Serial.println("waited 4th 2 secs");
  wheel2UpISR();
  delay(5);
  if (wheel1._interruptedUp) {
    wheel1.updateSpeed();
  }
  if (wheel2._interruptedUp) {  
    noInterrupts();
    start_time = micros();
    wheel2UpISR();
    end_time = micros();
    Serial.print("Start time: ");
    Serial.println(start_time);
    Serial.print("End time: ");
    Serial.println(end_time);
    Serial.print("Elapsed time: ");
    Serial.println(end_time - start_time);

    start_time = micros();
    wheel2.updateSpeed();
    end_time = micros();
    Serial.print("Start time: ");
    Serial.println(start_time);
    Serial.print("End time: ");
    Serial.println(end_time);
    Serial.print("Elapsed time: ");
    Serial.println(end_time - start_time);
    interrupts();
    while(1); 
    
  
    //Serial.println(wheel2._mph);                   //DEBEUG ONLY  
  }
  if (wheel3._interruptedUp) {
    wheel3.updateSpeed();
  }
  if (millis() % (wheel2._maxTime/5000) == 0) {     //check 5x the period for zerospeed
    wheel1.zeroMPH();
    wheel2.zeroMPH();
    wheel3.zeroMPH();
  }
  /*
  if (millis() % 50 == 0) {
    Serial.print(wheel2._numPulses%20);
    Serial.print("\t");
    Serial.print(wheel2._mph);                   //DEBEUG ONLY  
    Serial.print("\t");
    Serial.println();
  }
  */
}

