/*
  AnalogSmooth.cpp - Library to smooth analog signal 
  jitter by averaging concurrent readings.
  Created by Michael Thessel.
*/
#include "Arduino.h"
#include "AnalogSmoothInt.h"

/*
  Constructor
*/
AnalogSmoothInt::AnalogSmoothInt()
{
	this->_init(10);
}

/*
  Constructor
*/
AnalogSmoothInt::AnalogSmoothInt(unsigned int windowSize)
{
	this->_init(windowSize);
}

/*
  Initialzie the environment
*/
void AnalogSmoothInt::_init(unsigned int windowSize)
{
	// Restrict the size of the history array 
	// to >= 1 and < 100 items
	if (windowSize > 100) { windowSize = 100; }
	if (windowSize < 1) { windowSize = 1; }
	this->_windowSize = windowSize;
	
	this->_analogPointer = 0;
	this->_maxPointer = 0;
}

/*
  Perform smooting of analog input from given value 
*/
float AnalogSmoothInt::smooth(int value)
{
	// Return if we only keep track of 1 value
	if (this->_windowSize == 1) {
		return value;
	}

  // Subtract vaue to be removed
  this->_total -= this->_analog[this->_analogPointer];
  
	// Save the value to the history array	
	this->_analog[this->_analogPointer] = value;
	
	// Update total with new value
  this->_total += this->_analog[this->_analogPointer];

  // Calculate the moving average
	float avg = this->_total / (this->_maxPointer + 1);
	  
	// Keep track of how many items we have in the array
	if (this->_maxPointer < this->_windowSize - 1) {
		this->_maxPointer++;
	}
	 
	// Update the array pointer 
	this->_analogPointer++;
	if (this->_analogPointer == this->_windowSize) {
		this->_analogPointer = 0;
	}
	  
	// Return the average
	return avg;
}

/*
  Perform smooting of analog input from given pin 
*/
float AnalogSmoothInt::analogReadSmooth(uint8_t pin)
{
	// Read the pin
	int current = analogRead(pin);
	
	return this->smooth(current);
}
