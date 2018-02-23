void timedWheelMagnetISR() {
  rearWheel.readSensor();
  frontWheel.readSensor();
  interruptCount += 1;
}
