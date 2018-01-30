#include "ServoTimer2.h"
#include <Wire.h>

boolean debug = true;                  //Serial.print debug statements activate if debug = True

const int16_t pot = A3;             //Potentiometer pin
int UsrBtn = 4;                     //Button to turn on/off ABS functionality
int servoPin = 9;                   //PWM pin to control Servo

ServoTimer2 myservo;                // create servo object to control a servo
int servoMin = 800;                 //set this time(us) as the min pulse width corresponding to 0 degrees
int servoMax = 2200;                //set this time(us) as the max pulse width corresponding to 180 degrees

int absPos = 0;                     // variable to store the abs-controlled servo position
int pos = 0;                        // variable to store the servo position
int Vpot;                           // voltage of resistor divider for user brake input
/* Vpot_max0 = 3.9V = ang_min
 * Vpot_max  = 3.7V = 180-final_ang
 * Vpot_min  = 2.1V = 180
 */
int Vpot_max0 = 3.9 / 5 * 1024;     // voltage setpoint for min user input; Vpot_max0 
int Vpot_max = 3.7 / 5 * 1024;      // voltage setpoint for max user input of course-control, which then changes to fine-control
int Vpot_min = 2.1 / 5 * 1024;      // voltage setpoint for max user input
int final_ang = 45;                 // angle for slow controlled: (180-final ang) to 180
int ang_min = 70;                   // angle of loosest brake position

const int maxSpeed = 60;            // speed(mph) that speed values I2C were normalized to
int frontRearSpeed[2];              // data received for speed received over I2C
int n;                              // for checking number of bytes received over I2C


void setup()
{
  Wire.begin();                     // join i2c bus (address optional for master)
  pinMode(pot, INPUT);              // use as output
  myservo.attach(servoPin);         // attaches the servo on servoPin to the servo object
  pinMode(UsrBtn, INPUT);           //Set UsrBtn as an input for turning on/off ABS functionality
  if (debug) {
    Serial.begin(115200);
    Serial.println("started");
  }
}


void loop()
{
  Vpot = analogRead(pot);           // read position of user brake-input
  pos = nonABS();                   // calculate position based off of voltage divider containing user-input
  
  //Get speed over I2C from Arduino running "wheelSpeedSketch"
  n  = Wire.requestFrom(8, 4);      // request 4 bytes from slave device #8
  if( n == 4 ) {                    // if correct number of bytes received
    Wire.readBytes( (byte *) frontRearSpeed, 4);
  }
  
  absPos = antiLockBrake((float)frontRearSpeed[0]/1024*maxSpeed, (float)frontRearSpeed[1]/1024*maxSpeed, pos, absPos);
  checkABS();                       // sets brake limits, and overides ABS if UsrButton is off
  myservo.write((float)absPos/180*(servoMax-servoMin) + servoMin);
  
  if (debug) {
    //Serial.print(Vpot);
    //Serial.print("\t");
    //Serial.print("front speed: ");
    Serial.print((float)frontRearSpeed[0]/1024*maxSpeed);
    Serial.print("\t");
    //Serial.print("rear speed: ");
    Serial.print((float)frontRearSpeed[1]/1024*maxSpeed);
    Serial.print("\t");
  }

  if (debug) {
    Serial.println();
  }
  delay(100);                       // activate brake at about 10Hz
}

