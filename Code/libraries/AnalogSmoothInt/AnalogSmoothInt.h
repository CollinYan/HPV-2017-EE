/*
  AnalogSmooth.h - Library to smooth analog signal 
  jitter by averaging concurrent readings.
  Created by Michael Thessel.
*/
 
#ifndef AnalogSmoothInt_h
#define AnalogSmoothInt_h

#include "Arduino.h"

class AnalogSmoothInt
{
	public:
		AnalogSmoothInt(unsigned int windowSize);
		AnalogSmoothInt();
		float analogReadSmooth(uint8_t pin);
		float smooth(int value);
	private:
		unsigned int _windowSize;
		uint8_t _pin;
		int _analog[100];
		unsigned int _analogPointer;
		unsigned int _maxPointer;
    int _total;
		void _init(unsigned int windowSize);
};
#endif
