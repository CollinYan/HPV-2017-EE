int tireRollout = 2136;
  int numMagnets = 16;
  int minSpeed = 5;
  unsigned long _milesPerMagnetMicrosecondsPerHour = (float) tireRollout / 1e6 / 1.60934 / numMagnets * 1e6 * 60 * 60;  // near max value for unsigned int, change Div10 to Divxx to not overflow if change this val

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  Serial.println("-- initialized --");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print((float) 60 * 60 );   Serial.print('\t');
  Serial.print((float) 60 * 60 *tireRollout );   Serial.print('\t');
  Serial.print((float) 60 * 60 *tireRollout / 1e6  );   Serial.print('\t');
  Serial.print((float) 60 * 60 *tireRollout / 1e6 / 1.60934 );   Serial.print('\t');
  Serial.print((float) 60 * 60 * tireRollout / 1e6 / 1.60934 / numMagnets );   Serial.print('\t');
  int _maxTime = _milesPerMagnetMicrosecondsPerHour / minSpeed ;
  Serial.print( _maxTime);  Serial.print('\t');
  Serial.println();
  delay(1000);
}
