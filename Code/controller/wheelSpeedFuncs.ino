/*continuous*/
void wheelSpeed() {
  if (wheel1._interruptedUp) {
    wheel1.updateSpeed();                                       // updates wheelspeed and sets _interruptedUp to false
    wheel1._mphX100 = smoothedWheel1.smooth(wheel1._mphX100);   // smooths wheelspeed, but set to not actually smooth
  } else {
    wheel1.zeroMPH();                                           // check if the wheel has been stopped too long, aka slower than minSpeed
  }
  if (wheel2._interruptedUp) {  
    wheel2.updateSpeed();
    wheel2._mphX100 = smoothedWheel2.smooth(wheel2._mphX100);
    int msTick = wheel2._centerToCenter/1000;                 // time taken of the last wheel tick
    accelIndice = myAccelSpeed._arrayPos-msTick/(1000/freq);  // calculates the time in 10ms units, of the time half a wheel tick took
    accelIndice = (accelIndice+10)%10;                        // wraps index, fixed at storing 10 values inside accelSpeed object
  } else {
    wheel2.zeroMPH();
  }
  if (wheel3._interruptedUp) {
    wheel3.updateSpeed();
    wheel3._mphX100 = smoothedWheel3.smooth(wheel3._mphX100);
  } else {
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

