//Timer2 interrupt: read and check both wheel sensors
ISR(TIMER2_COMPA_vect) {
  rearWheel.readSensor();
  frontWheel.readSensor();
  interruptCount += 1;
}

/* What to send over I2C when requested by master
 * Sends 2 integers as 4 bytes, frotnRearSpeed
 */
void requestEvent() {
  Wire.write( (byte *) frontRearSpeed, 4); // respond with message of 4 bytes
}

void setupTimer2() {
  /* Setup Timer2 for interrupts
   *  Currently set to: 2kHz
   */

  noInterrupts();           // disable all interrupts
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 101;            // preload timer 256- 16MHz/(1024*100Hz) //timer frequancy is 100Hz
  TCCR2B |= (1 << CS12);
  TCCR2B |= (1 << CS10);    // 1024 prescaler
  TIMSK2 |= (1 << TOIE2);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts


  /*
  cli();//stop interrupts
  //set timer2 interrupt at 2kHz
  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B
  TCNT2  = 0;//initialize counter value to 0
  // set timer count for 2khz incrementsv(4khz - >ocr2a = 64
  OCR2A = 64;// 2khz = (16*10^6) / (2000*64) - 1
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  //set CS22 for 64 prescalaer for Timer2
  TCCR2B |= (1 << CS22); 
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  sei();//allow interrupts
  */
}
