/*
  ParkingLock.cpp - Library to lock brakes given lever being held down
  Created by Harrison Hsueh.
*/
#include "Arduino.h"
#include "ParkingLock.h"

/*
  Constructor
*/
ParkingLock::ParkingLock()
{
	this->_init(1000,5000,10);
}

/*
  Constructor
*/
ParkingLock::ParkingLock(unsigned int ms, unsigned int freq,int tol)
{
	this->_init(ms, freq, tol);
}

/*
  Initialzie the environment
*/
void ParkingLock::_init(unsigned int ms, unsigned int freq, int tol)
{
  if (ms < 1000/freq) {
    this->_noLock = true;
    return;
  }
	// calculate _windowSize given call frequency and desired window time in milliseconds
  this->_windowSize = freq*ms/1000;
	
	this->_locked = false;
	this->_timeAtChange = 0;
  this->_minVal = 0;
  this->_lockedOutput = 0;
  this->_time = 0;
  this->_tol = tol;
}

/*
  process val to see if it should lock or not
*/
int ParkingLock::processParkingLock(int val)
{
  if (this->_noLock) {
    return val;
  }
  this->_time+=1;
  if (this->_locked == true) {                                          //if locked
    if (val > this->_minVal+ 2*this->_tol-2) {                                               //unlock
      this->_locked = false;
      this->_updateTimeAndVals(val);
      //Serial.println("unlocked");
    }
    else {                                                                //stay locked
      this->_minVal = min(this->_minVal, val);
      //Serial.println("staying locked");
      val =this->_lockedOutput;
    }
  }
  
  else if (this->_locked != true) {                                     //if not locked
    if (this->_lockedOutput-this->_tol<val && val<this->_lockedOutput+this->_tol) {         //within lock range
      if (this->_time - this->_timeAtChange > this->_windowSize) {                                      //within range long enough, lock
        this->_locked = true;
        this->_lockedOutput = val;
        this->_minVal = val;
        //Serial.println("engaging lock");
      } 
      else {                                                                //within range but not long enough yet                                                      
        //Serial.println("within range but not long enough");
      }
    } 
    else {                                                                //not within range, just update                                  
      this->_updateTimeAndVals(val); 
      //Serial.println("not within range");
    }
  }
  return val;
}


void ParkingLock::_updateTimeAndVals(int val) {
  this->_lockedOutput = val;
  this->_timeAtChange = this->_time;
}

/*
  Perform process for locking from given pin 
*/
int ParkingLock::analogReadParkingLock(uint8_t pin)
{
	// Read the pin
	int val = analogRead(pin);
	return this->processParkingLock(val);
}
