/*called by brake which is 10Hz*/
void antiLockBrake() {
  //antiLockBrake(myAccelSpeed._vehicleSpeedX10, wheel2._mphX10, 100, 100);
}

int antiLockBrake(float vehicleSpeed, float wheelSpeed, int desiredBrake, int absBrake) {
  float slip = (vehicleSpeed - wheelSpeed) / vehicleSpeed;
  if (vehicleSpeed < 0.001) {             //if stopped, slip calculates to infinity, set slip = 0
    slip = 0;
  }

  float desiredSlip = 0.1;  
  int Kp = 5;
  float e = desiredSlip - slip;           //error is the difference in desired and actual slip
  absBrake = absBrake + Kp * e;           //proportional control

  #ifdef SERIAL_PORT_LOG_ENABLE
    /*
    Serial.print("  vehicleSpeed: ");
    Serial.print(vehicleSpeed);
    Serial.print("\t");
    Serial.print("  wheelSpeed: ");
    Serial.print(wheelSpeed);
    Serial.print("\t");
    */ 
    //Serial.print("  slip: ");
    Serial.print(slip);
    Serial.print("\t");
    /*
    Serial.print(absBrake);
    Serial.print("\t");
    */
  #endif
  
  absBrake = min(desiredBrake, absBrake);   //if user-desired brake is less than absBrake, then the brake shouldn't brake harder than desired
  return absBrake;
}



