#include "AntiLockBrake.h"
int wheelSpeeds[] = {999,999,980,970,960,950,940,930,920,910,
                     899,899,880,870,860,750,640,530,720,710};
int vehicleSpeeds[] = {999,999,980,970,960,950,940,930,920,910,
                     899,899,880,870,860,790,780,760,720,710};
float kP = 0.05;
int maxSlip = 20;
int minBrake = 100;
AntiLockBrake testBrake(kP, 99, 99, maxSlip, minBrake);
int desiredBrake = 180;
int absOutput = 0;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  for (int i = 0; i <= sizeof(wheelSpeeds); i++) {
    absOutput = testBrake.processABS(vehicleSpeeds[i], wheelSpeeds[i], desiredBrake);
    Serial.print(vehicleSpeeds[i]); Serial.print("\t");
    Serial.print(wheelSpeeds[i]); Serial.print("\t");
    Serial.print(absOutput); Serial.print("\t");
    delay(100);
  }
  // put your main code here, to run repeatedly:

}
