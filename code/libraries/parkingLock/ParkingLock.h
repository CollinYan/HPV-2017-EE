/*
  parkingLock.h - Library to lock after x readings 
  Created by Harrison Hsueh.
*/
 
#ifndef ParkingLock_h
#define ParkingLock_h

#include "Arduino.h"

class ParkingLock
{
	public:
		ParkingLock(unsigned int ms, unsigned int freq, int tol);
		ParkingLock();
		int analogReadParkingLock(uint8_t pin);
		int processParkingLock(int value);
	private:
    void _init(unsigned int ms, unsigned int freq, int tol);
		unsigned int _windowSize;
		uint8_t _pin;
    bool _locked;                     // True if tilt lever is held in same position for 3 seconds = 3000 ms
    unsigned long _timeAtChange;      // Time at which the brake lever position last changed
    int _minVal;                      // Minimum value while locked, so if current val ever higher, unlock
    int _lockedOutput;                // Locked tilt lock value
    void _updateTimeAndVals(int val);        //
    unsigned long _time;              // time in increments of time between calls of processLock(), if 100Hz, overflows in 231days
    bool _noLock;
    int _tol;                // to invoke locking, must be within value+- _tol
};
#endif
