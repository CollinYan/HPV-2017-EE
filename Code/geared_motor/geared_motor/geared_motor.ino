bool in1 = 1;
bool in2 = 0;
int pwm = 255;

const int in1Pin = 7;
const int in2Pin = 8; 
const int pwmPin = 6;
const int potPin = A0;

int potVal = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(pwmPin, OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(potPin);
  pwm = potVal/4;
  digitalWrite(in1Pin, in1);
  digitalWrite(in2Pin, in2);
  analogWrite(pwmPin, pwm);
  delay(10);
}
