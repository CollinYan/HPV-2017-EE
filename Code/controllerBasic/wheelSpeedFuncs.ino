/*continuous*/
void wheelSpeed() {
  if (wheel1._interruptedUp) {
    wheel1.updateSpeed();
  }
  if (wheel2._interruptedUp) {  
    wheel2.updateSpeed();
  }
  if (wheel3._interruptedUp) {
    wheel3.updateSpeed();
  }
  if (millis() % (wheel2._maxTime/5000) == 0) {     //check 5x the period for zerospeed
    wheel1.zeroMPH();
    wheel2.zeroMPH();
    wheel3.zeroMPH();
  }
}

/*external interrupts*/
void wheel1UpISR() {
  wheel1.readTimeUp();
}
void wheel2UpISR() {
  wheel2.readTimeUp();
}
void wheel3UpISR() {
  wheel3.readTimeUp();
}

