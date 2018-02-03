const int potPin = A0;   // Braking input: ranges from min value to max value, should convert to servo value 0-280 deg
const int tiltPin = A1;  // High or low voltage "bool" 
const int pwmPin1 = 5;   // Output to the tilt lock servo
const int pwmPin2 = 6;   // Output to the brake servo for one wheel
const int pwmPin3 = 7;   // Output to the brake servo for the second wheel
             
int potVal;              // Ideal hardware design for 0V to 3.33V, which translates to max range of 0 to 1024 ADC output
bool tiltVal;

bool locked;
int tiltOutput;
int brakeOutput;
int minServoRange;
int maxServoRange;


void setup() {
  pinMode(pwmPin1, OUTPUT);  
  pinMode(pwmPin2, OUTPUT);
}

void loop() {
  potVal = analogRead(potPin);    // read values from brake & tilt input
  tiltVal = digitalRead(tiltPin); // read in boolean value 

  tiltOutput = convertTiltOutput(tiltVal);
  brakeOutput = convertBrakeOutput(potVal);

  digitalWrite(pwmPin1, tiltOutput);
  digitalWrite(pwmPin2, brakeOutput);  // outputs the same value for both wheels
  digitalWrite(pwmPin3, brakeOutput);
  delay(10);
}
