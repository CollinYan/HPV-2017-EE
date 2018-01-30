#include "ServoTimer2.h"
#include <Wire.h>

const int16_t pot = A3;     //Potentiometer pin
int UsrBtn = 4;             //Button to turn on Servo
int servoPin = 9;

ServoTimer2 myservo;  // create servo object to control a servo
int servoMin = 800;
int servoMax = 2200;

int absPos = 0;
int pos = 0;                // variable to store the servo position
int Vpot;                   // voltage of resistor divider
int Vpot_max0 = 3.9 / 5 * 1024; //
int Vpot_max = 3.7 / 5 * 1024; //
int Vpot_min = 2.1 / 5 * 1024; //
int final_ang = 45;         // angle for slow controlled (180-final ang) to 180
int ang_min = 70;           // angle of loosest

const int maxSpeed = 60;
int frontRearSpeed[2];
int n; //number of bytes from i2c

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  pinMode(pot, INPUT); // use as output
  myservo.attach(servoPin);  // attaches the servo on servoPin to the servo object
  pinMode(UsrBtn, INPUT);  //Set UsrBtn as an input
  Serial.begin(115200);
}

void loop()
{
  //Serial.print(interruptCount);
  //Serial.print("\t");

  Vpot = analogRead(pot);
  Serial.print(Vpot);
  Serial.print("\t");
  if (Vpot > Vpot_max) {
    pos = 180 - final_ang - ((float)Vpot - Vpot_max) / (Vpot_max0 - Vpot_max) * (180 - final_ang);
    if (pos < ang_min) {
      pos = ang_min;
    }
  }
  else {
    pos = 180 - ((float)Vpot - Vpot_min) / (Vpot_max - Vpot_min) * final_ang;
    if (pos > 180) {
      pos = 180;
    }
  }

  n  = Wire.requestFrom(8, 4);    // request 4 bytes from slave device #8
  if( n == 4 ) {
    Wire.readBytes( (byte *) frontRearSpeed, 4);
  }
  
  absPos = abs_func((float)frontRearSpeed[0]/1024*maxSpeed, pos, (float)frontRearSpeed[1]/1024*maxSpeed);
  Serial.print((float)frontRearSpeed[0]/1024*maxSpeed);
  Serial.print("\t");
  Serial.print((float)frontRearSpeed[1]/1024*maxSpeed);
  Serial.print("\t");
  
  checkABSOFFButton();
  if (absPos < 180-final_ang) {
    absPos = pos;
  }
  else if (absPos > 180) {
    absPos = 180;
  }
  //absPos = 150;
  myservo.write((float)absPos/180*(servoMax-servoMin) + servoMin);
  Serial.println();
  delay(1); 
}

void checkABSOFFButton() {
  Serial.print(pos);
  Serial.print("\t");
  Serial.print(absPos);
  Serial.print("\t");
  if (digitalRead(UsrBtn) == 1) {
  }
  else {
    
    absPos =pos;
  }
}







