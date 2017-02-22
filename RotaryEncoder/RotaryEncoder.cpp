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

int RotaryEncoder::grayToBin(int grayVal, int nbits ) {
  // Bn-1 = Bn XOR Gn-1   source of method:  http://stackoverflow.com/questions/5131476/gray-code-to-binary-conversion but include correction 
    int binVal = 0;
  	bitWrite(binVal, nbits - 1, bitRead(grayVal, nbits - 1)); // MSB stays the same
	for (int b = nbits - 1; b > 0; b-- ) {
		// XOR bits
		if (bitRead(binVal, b) == bitRead(grayVal, b - 1)) { // binary bit and gray bit-1 the same
			bitWrite(binVal, b - 1, 0);
		}
		else {
   			bitWrite(binVal, b - 1, 1);
		}
	}
	return binVal;
}

int RotaryEncoder::getPosition(const int *pins) {
	// Declare a variable which will be the answer
	int pos = 0;
	
	// Write bits into it - in gray code though
	for (int i=0; i<8; i++) {
		bitWrite(pos, i, !digitalRead(pins[7-i]));
	}
	// Convert the Gray value of position to Decimal
	return grayToBin(pos, 8);
}
