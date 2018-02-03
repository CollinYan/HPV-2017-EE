const int potPin = A0;   // Braking input: ranges from min value to max value, should convert to servo value 0-280 deg
const int tiltPin = A1;  // High or low voltage "bool" 
const int pwmPin1 = 5;   // Output to the tilt lock servo
const int pwmPin2 = 6;   // Output to the brake servo for one wheel
const int pwmPin3 = 7;   // Output to the brake servo for the second wheel

int potVal;    // value read in from brake lever

bool locked = false;              // True if lever is held in same position for 3 seconds = 3000 ms
int servoVal;                     // potval converted to servo val
unsigned long timeAtChange = 0;   // Time at which the brake lever position last changed
int prevServoVal = 0;
int lockedVal = 0;

int servoOutput;             // same servo output for brake and tilt lock
int minServoRange = 0;
int maxServoRange = 280;


void setup() {
  pinMode(pwmPin1, OUTPUT);  
  pinMode(pwmPin2, OUTPUT);
  pinMode(pwmPin3, OUTPUT);
}

void loop() {
  potVal = analogRead(potPin);
  servoVal = convertToServo(potVal);

  if (locked == true) {
    if (servoVal > prevServoVal) {
      locked = false;
      servoOutput = servoVal;
      updateTimeAndVals();
    }
    else {
      servoOutput = lockedVal;
      updateTimeAndVals();
    }
  }
  
  else if (locked != true) {
    if (servoVal != prevServoVal) {
      servoOutput = servoVal;
      updateTimeAndVals();
    } 
    else {
      if (millis() - timeAtChange > 3000) {  // dont update timeatchange
        locked = true;
        lockedVal = servoVal;
        servoOutput = servoVal;
      }
    }
  }

  digitalWrite(pwmPin1, servoOutput);   
  digitalWrite(pwmPin2, servoOutput);  // outputs the same value for both wheels and tiltlock
  digitalWrite(pwmPin3, servoOutput);
  delay(10);
}
