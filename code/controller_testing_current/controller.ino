#include "Servo.h"
#include "AnalogSmoothInt.h"

const int batteryPin = A5;    // Battery voltage divided down by 10
const int brakePin1 = A0;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int brakePin2 = A1;     // Braking input: ranges from min value to max value, should convert to servo value 0-180 deg
const int tiltPin = A2;       // Tilt lever input: ranges from the same values as potpin
const int brakePWMPin1 = 5;   // Output to the brake servo for one wheel
const int brakePWMPin2 = 6;   // Output to the brake servo for the second wheel 
const int tiltPWMPin = 7;     // Output to the tilt lock servo

const int batteryVoltageCutoff = 3.6*4/3.3*1023/10;  // 
int batteryVoltage;
bool batteryGood;
float brakeRead1;             // value read in from brake lever
float tiltRead;               // value read in from tilt lever

bool locked = false;                  // True if tilt lever is held in same position for 3 seconds = 3000 ms
unsigned long timeAtChange = 0;       // Time at which the brake lever position last changed
int minTiltServoOutput = 0;
int lockedTiltServoOutput = 0;        // Locked tilt lock value

int tiltServoOutput;                  // servo output for tiltlock
int brakeServoOutput;                 // servo output for brake

int minValue = 2.380 * 1023/3.3;      //1.1V to 1.2V or 2.38V to 2.93V depending on potentiometer position
int maxValue = 2.930 * 1023/3.3;
int minHighTime = 800;                //min High time for PWM to servo, according to specs
int maxHighTime = 2200;               //max High time for PWM to servo, according to specs
int minServoRange = 100;              //0 degrees would output minHighTime
int maxServoRange = 175;              //180 degrees would ouput maxHighTime

Servo brakeServo1;
Servo tiltServo;

/*for smoothing break input*/
AnalogSmoothInt smoothedBrake1 = AnalogSmoothInt(3);

int periodBrakeRead = 10;             //period of brake input reading in ms
boolean leverReadTicked = 0;          //keep track of whether brake was read

void setup() {  
  brakeServo1.attach(brakePWMPin1,minHighTime,maxHighTime);
  tiltServo.attach(tiltPWMPin,minHighTime,maxHighTime);  
  
  Serial.begin(9600);
  Serial.println("-- initialized --");
  Serial.println();
}

void loop() {
  batteryVoltage = analogRead(batteryPin);
  batteryGood = batteryVoltage>batteryVoltageCutoff;
  //Serial.print(batteryVoltage*3.3*10/1023);
  //Serial.print("\t");
  if (!(millis()%periodBrakeRead) && !leverReadTicked && batteryGood) {
    /*brake 1*/
    brakeRead1 = smoothedBrake1.analogReadSmooth(brakePin1);
    brakeServoOutput = convertToServo(brakeRead1);
    //brakeServo1.write(brakeServoOutput); 

    /*tilt*/
    tiltRead = analogRead(tiltPin);
    //tiltServoOutput = convertToServo(tiltRead);
    
    //tiltServoOutput = brakeServoOutput;
    
    //Serial.println("voltage");
    /*
    Serial.print(brakeRead1);
    Serial.print("\t");
    Serial.print(tiltServoOutput);
    Serial.print("\t");
    
    processTiltServoOutput();
    Serial.print(tiltServoOutput);
    Serial.print("\t");
    */
    
    //tiltServoOutput = millis()/10000+150;
    if (Serial.available() > 0) {
            // read the incoming byte:
            char incomingByte = Serial.read();

            // say what you got:
            Serial.print("I received: ");
            Serial.print(incomingByte, DEC);
            //char keyboard[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
            String keyboard = "abcdefg";
            int angles[] = {130, 140, 150, 160, 165, 170, 175};
            for (int i=0; i<=23; i++) {
                tiltServoOutput = 130+2*i;
                Serial.print(tiltServoOutput);
                Serial.print("\t");
                Serial.println("");
                brakeServo1.write(tiltServoOutput);  
                delay(6000);
            }        
            for (int i=0; i<=23; i++) {
                tiltServoOutput = 176-2*i;
                Serial.print(tiltServoOutput);
                Serial.print("\t");
                Serial.println("");
                brakeServo1.write(tiltServoOutput); 
                delay(6000);
            }
            Serial.print("\t"); 
            Serial.print(tiltServoOutput);
            Serial.print("\t");
            Serial.println("");
    }
    tiltServoOutput = 130;
    tiltServoOutput = constrain(tiltServoOutput,100,180);
    brakeServo1.write(tiltServoOutput); 
    tiltServo.write(tiltServoOutput); 
    
    leverReadTicked = 1;
  } else if (millis()%periodBrakeRead) {
    leverReadTicked = 0;
  }

}
