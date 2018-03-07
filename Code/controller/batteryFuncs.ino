void checkBat(){
  batteryVoltage = analogRead(batteryPin);
  batteryGood = batteryVoltage>batteryVoltageCutoff;
}

