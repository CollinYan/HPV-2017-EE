void checkBat(){
  batteryVoltage = analogRead(batteryPin);
  batteryGood = batteryVoltage>batteryVoltageCutoff;
  //Serial.print(batteryVoltage*3.3*10/1023);
  //Serial.print("\t");
}

