#include <StepperControl.h>

StepperControl::StepperControl(const int* stepper_pins) {
	// Set initial values of private variables
	stage = 0;
	pins[0] = stepper_pins[0];
	pins[1] = stepper_pins[1];
	pins[2] = stepper_pins[2];
	pins[3] = stepper_pins[3];
	step_delay = 100;

	// Set pin to output mode
	pinMode(pins[0], OUTPUT);
	pinMode(pins[1], OUTPUT);
	pinMode(pins[2], OUTPUT);
	pinMode(pins[3], OUTPUT);

	// Set value of OUTPUTs to LOW
	digitalWrite(pins[0], LOW);
	digitalWrite(pins[1], LOW);
	digitalWrite(pins[2], LOW);
	digitalWrite(pins[3], LOW);
}

void StepperControl::set_step_delay(int delay) {
	step_delay = delay;
	return;
}

void StepperControl::step_up() {
	// This will be a dispatch on the number "Stage"
	switch(stage) {
		
		case 0:
			digitalWrite(pins[3], LOW);
			digitalWrite(pins[0], HIGH);
			delay(step_delay);
			//digitalWrite(pins[0], LOW);
			stage = 1;
			break;

		case 1:
			digitalWrite(pins[0], LOW);
			digitalWrite(pins[1], HIGH);
			delay(step_delay);
			//digitalWrite(pins[1], LOW);
			stage = 2;
			break;
		case 2:
			digitalWrite(pins[1], LOW);
			digitalWrite(pins[2], HIGH);
			delay(step_delay);
			//digitalWrite(pins[2], LOW);
			stage = 3;
			break;
		case 3:
			digitalWrite(pins[2], LOW);
			digitalWrite(pins[3], HIGH);
			delay(step_delay);
			//digitalWrite(pins[3], LOW);
			stage = 0;
			break;
	}
}

void StepperControl::step_down() {
	// This will also be a dispatch on the number "Stage"
	switch(stage) {
		
		case 0:
			digitalWrite(pins[3], LOW);
			digitalWrite(pins[2], HIGH);
			delay(step_delay);
			digitalWrite(pins[2], LOW);
			stage = 3;
			break;

		case 1:
			digitalWrite(pins[0], LOW);
			digitalWrite(pins[3], HIGH);
			delay(step_delay);
			digitalWrite(pins[3], LOW);
			stage = 0;
			break;
		case 2:
			digitalWrite(pins[1], LOW);
			digitalWrite(pins[0], HIGH);
			delay(step_delay);
			digitalWrite(pins[0], LOW);
			stage = 1;
			break;
		case 3:
			digitalWrite(pins[2], LOW);
			digitalWrite(pins[1], HIGH);
			delay(step_delay);
			digitalWrite(pins[1], LOW);
			stage = 2;
			break;
	}
}

void StepperControl::step(int steps) {
	// Check if you have to use step_up or step_down
	// Then run a while loop to step_up (down) that much
	if (steps > 0) { 
		while (steps > 0) {
			step_up();
			steps--;
		}
	}
	else if (steps < 0) {
		while (steps < 0) {
			step_down();
			steps++;
		}
	}

	for (int i=0; i<4; i++)
		digitalWrite(pins[i], LOW);
}
