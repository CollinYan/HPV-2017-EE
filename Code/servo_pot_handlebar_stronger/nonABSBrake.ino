int nonABS() {
  if (Vpot > Vpot_max) {            // if user is in the course-control region
    pos = 180 - final_ang - ((float)Vpot - Vpot_max) / (Vpot_max0 - Vpot_max) * (180 - final_ang);
    if (pos < ang_min) {
      pos = ang_min;
    }
  }
  else {                            // else user input is in the fine-control region
    pos = 180 - ((float)Vpot - Vpot_min) / (Vpot_max - Vpot_min) * final_ang;
    if (pos > 180) {
      pos = 180;
    }
  }
  return pos;
}
  
void checkABSOFFButton() {
  if (debug){
    //Serial.print("pos: ");
    Serial.print(pos/10);
    Serial.print("\t");
    
    //Serial.print("absPos: ");
    Serial.print(absPos/10);
    Serial.print("\t");
    Serial.print(digitalRead(UsrBtn));
    Serial.print("\t");
  }
  
  if (!digitalRead(UsrBtn)) {       // if ABS button is off
    absPos =pos;
  }

  if (absPos < 180-final_ang*2) {
    absPos = pos;
  }
  if (absPos < ang_min) {
    absPos = ang_min;
  }
}
