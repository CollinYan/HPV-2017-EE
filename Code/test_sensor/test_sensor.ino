void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print(digitalRead(12));
  //Serial.print("\t");
  Serial.println(digitalRead(13));
}
