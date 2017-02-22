#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <Arduino.h>

class RotaryEncoder {
public:
	RotaryEncoder() {};			// Constructor
	int invert(int);			// For Gray->Dec conversion
	void grayToDecimal(int &, int bl = 8);	// Gray->Decimal
	int grayToBin(int, int);
	int getPosition(const int *);		// Finally used function
};

#endif
