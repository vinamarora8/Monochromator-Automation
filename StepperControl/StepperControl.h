#ifndef STEPPERCONTROL_H
#define STEPPERCONTROL_H

#include <Arduino.h>

class StepperControl {
private:
	int stage;
	int pins[4];
	int step_delay;
	void step_up();
	void step_down();

public:
	StepperControl(const int*);
	void set_step_delay(int);
	void step(int steps);
};

#endif
