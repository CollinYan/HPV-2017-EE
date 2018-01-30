const int numReadings = 10;

int readings[numReadings];
int readIndex = 0;
int total = 0;
int current_abs_position;
bool abs_activate = false;

void abs_setup() {
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void abs_loop(float wheel_speed, float vehicle_speed) { // taken from online and removed the averaging part and made it only continuously update total
  // subtract the last reading:
  total = total - readings[readIndex];
  // calculate the instantaneous slip error:
  readings[readIndex] = calc_slip_diff(0.1, wheel_speed, vehicle_speed); // get wheel speed from wheel speed function
  // add the instantaneous slip error to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
}

long calc_slip_diff(long desired_slip, float wheel_speed, float vehicle_speed) { // calculates the difference in slip ratios of a wheel
  return desired_slip - calc_slip(wheel_speed, vehicle_speed);
  }

long calc_slip(float wheel_speed, float vehicle_speed) {
  return (vehicle_speed - wheel_speed) / vehicle_speed;
}

long proportional_control(double k, long error) {
  return -k * error; // calculates proportional control
}

long integral_control(double k) {
  return -k * total; // total is continuously updated as sum of slip over the past 10 executions
}



long abs_func(float wheel_speed, int user_position, float vehicle_speed) { // returns optimal braking position based on controls

  abs_loop(wheel_speed, vehicle_speed);

  long slip = calc_slip(wheel_speed, vehicle_speed);
  long slip_diff = calc_slip_diff(0.1, wheel_speed, vehicle_speed); // gets slip ratio difference, desired slip = 0.1
  long control;
  long abs_position;
  
  control = proportional_control(10, slip_diff) + integral_control(1); // summing together P and I controls using some arbitrary constants
  abs_position = round(180 + control);
  
  if (user_position <= 71) { // no brake input
    current_abs_position = user_position;
    abs_activate = false;
    return user_position;
  }

  else if (abs_activate == true) {
    current_abs_position = min(abs_position, user_position);
    return min(current_abs_position, user_position); // returns an "optimal" braking position
  }

  else if (slip_diff > .05) {
    abs_activate = true;
  }
}




// only when braking at a certain hardness
// wrong k values
// 

// take in wheel speeds
// take in desired braking position
// output actual braking position
// desired slip
// 1 - (f-r)/lv
// find a buffer increase decrease brake
// within buffer but drops very fast
// desired slip ratio: 0.8
// if not slipping as much, increase braking power
// u(t) is error value

// gradual increase
// P I D


