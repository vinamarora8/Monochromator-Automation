#include <Arduino.h>
#include <RotaryEncoder.h>

int RotaryEncoder::invert(int obit) {
	// input is 1 or 0
	// 1 -> 0 ; 0 -> 1
	return (obit+1)%2;
}

void RotaryEncoder::grayToDecimal(int &gray_val, int bl) {
	// Recursion ender
	if (bl == 0)
		return;

	// If current bit is 1, invert the next
	// Check if next exists or not
	if (bitRead(gray_val, bl-1) == 1 && bl > 1)
		bitWrite(gray_val, bl-2, invert(bitRead(gray_val, bl-2)));
	
	// Go to next bit
	grayToDecimal(gray_val, bl-1);
}

int RotaryEncoder::getPosition(const int *pins) {
	// Declare a variable which will be the answer
	int pos = 0;
	
	// Write bits into it - in gray code though
	for (int i=0; i<8; i++) {
		Serial.print(digitalRead(pins[i]));
		bitWrite(pos, i, digitalRead(pins[i]));
	}
	Serial.println();
	// Convert the Gray value of position to Decimal
	grayToDecimal(pos);
	return pos;
}
