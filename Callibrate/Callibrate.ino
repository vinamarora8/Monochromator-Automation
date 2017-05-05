#include <StepperControl.h>
#include <RotaryEncoder.h>
#include <EEPROM.h>

// Pins for Rotary Encoder and Stepper Motor
const int RotEnc[] = {2,3,4,5,6,7,8,9};
const int StepMot[] = {10,11,12,13};

// Libraries for operating the above
RotaryEncoder rotlib;
StepperControl stepctrl(StepMot);

void setup() {
	// Initialize Serial Monitor
	Serial.begin(9600);
	
	// Set up Rotary Encoder Pins
	for (int i=0; i<8; i++) {
		pinMode(RotEnc[i], INPUT);
		digitalWrite(RotEnc[i], HIGH);
	}
	
	// Stepper Motor already set up by the library
	stepctrl.set_step_delay(100);

	// Print 1 to indicate "READY"
	Serial.println(1);
}

void loop() {
	// Main Code
	// Read Serial Input
	if (Serial.available() > 0) {
		int steps = Serial.parseInt();

    if (steps == 250)
      Serial.println(1);
    
		// If steps == 0, save the RotEnc state
		// Write only if the state is different than the already stored one
		// to increase EEPROM life
		if (steps == 0){
			int current_val = rotlib.getPosition(RotEnc);
			if (current_val != EEPROM.read(0))
				EEPROM.write(0, current_val);
			Serial.println("DONE");
      Serial.println(current_val);
      Serial.print("New init-val ");
      Serial.println(EEPROM.read(0));
		}

		// Otherwise take as many steps as the input
		else if (steps <= 200) {
			stepctrl.step(steps);
			// Print 11 to indicate steps were taken
			Serial.println(1);
		}
	}
}
