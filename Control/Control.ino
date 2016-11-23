/* TODO
 *  - Check Resolution values
 *  - Check stepper polarity
 */

#include <RotaryEncoder.h>
#include <StepperControl.h>
#include <EEPROM.h>

const int RotEnc[] = {2,3,4,5,6,7,8,9};
const int StepMot[] = {10,11,12,13};
RotaryEncoder rotlib;
StepperControl stepctrl(StepMot);

int current_wavelength = 300;

void setup() {
  // Initialize Serial monitor
  Serial.begin(9600);
  
  // Set up Rotary Encoder Pins
  for (int i=0; i<8; i++) {
    pinMode(RotEnc[i], INPUT);
    digitalWrite(RotEnc[i], HIGH);
  }

  // Set up stepper motor
  // 
  // 
  //

  // Initialize the motor
  initialize();
  
}

void loop() {
  // main code
  // Read serial input
  if(Serial.available() > 0) {
    int inp = Serial.read();

    // Check if this is a wavelength, a command or a trash number
    if (inp <= 700 && inp >= 300)
      RTControl(inp);
    else if (inp = 701)
      initialize();
    else
      Serial.println(0);
  }

}

void initialize() {
  // Read initial rotary encoder value (stored in EEPROM address 0)
  int init_val = EEPROM.read(0);

  // Read current rotary encoder value
  int current_val = rotlib.getPosition(RotEnc);

  // Goto Init Val
  //
  // Calculate number of steps it takes to reach init val
  // Resolutions: Stepper motor - 200 steps per cycle
  //              Rotary Encoder- 256 steps per cycle
  int steps = (init_val - current_val)*(200/256);
  //
  // Travel that many steps
  stepctrl.step(steps);

  // Veryify
  // If not reached, recall this function
  current_val = rotlib.getPosition(RotEnc);
  if (init_val != current_val)
    initialize();

  // Testing helper
  Serial.println(1);
}

void RTControl(int wavelength) {
  // Calculate number of steps to move
  // Resolution of Stepper motor : 200 steps per cycle
  int steps = (wavelength - current_wavelength)*(200/700);

  // Travel that many steps
  stepctrl.step(steps);

  // Update current wavelength
  current_wavelength = wavelength;
  
  // Testing helper
  Serial.println(1);
}
