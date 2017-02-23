/* TODO
 *  - Check Resolution values
 */

#include <RotaryEncoder.h>
#include <StepperControl.h>
#include <EEPROM.h>

// Pins for Rotary Encoder and Stepper Motor
const int RotEnc[] = {2,3,4,5,6,7,8,9};
const int StepMot[] = {10,11,12,13};

// Libraries for the above
RotaryEncoder rotlib;
StepperControl stepctrl(StepMot);

// Minimum wavelength of my Monochromator is 300nm 
int current_wavelength = 300;

void setup() {
  // Initialize Serial monitor
  Serial.begin(9600);
  Serial.println("Setting pins for Rotary Encoder");
  // Set up Rotary Encoder Pins
  for (int i=0; i<8; i++) {
    pinMode(RotEnc[i], INPUT);
    digitalWrite(RotEnc[i], HIGH);
  }

  // Set up stepper motor
  // 
  stepctrl.set_step_delay(100);
  //

  // Initialize the motor
  initialize();
  
}

void loop() {
  // main code
  // Read serial input
  if(Serial.available() > 0) {
    int inp = Serial.parseInt();

    // Check if this is a wavelength, a command or a trash number
    if (inp <= 700 && inp >= 300)
      RTControl(inp);
    else if (inp == 701)
      initialize();
    else
      Serial.println(0);
  }

}

void initialize() {
  Serial.println("Initializing");
  // For testing purposes:
  //EEPROM.write(0, 10);
  
  // Read initial rotary encoder value (stored in EEPROM address 0)
  int init_val = EEPROM.read(0);
  
  Serial.print("init-val = ");
  Serial.println(init_val);
  
  // Read current rotary encoder value
  int current_val = rotlib.getPosition(RotEnc);
  
  Serial.print("Shaft currently at: ");
  Serial.println(current_val);
  
  // Goto Init Val
  //
  // Calculate number of steps it takes to reach init val
  // Resolutions: Stepper motor - 200 steps per cycle
  //              Rotary Encoder- 256 steps per cycle
  int steps = (init_val-current_val);
  steps *= 200;
  steps /= 256;

  Serial.print("Steps required: ");
  Serial.println(steps);

  // Travel that many steps
  stepctrl.step(steps);

  // Testing helper
  Serial.println(1);
}

void RTControl(int wavelength) {
  // Calculate number of steps to move
  // Resolution of Stepper motor : 200 steps per cycle
  int steps = (wavelength - current_wavelength);
  steps *= 2;
  steps /= 7;

  Serial.print("Current wavelength: ");
  Serial.println(current_wavelength);
  // Travel that many steps
  stepctrl.step(steps);

  Serial.print("Steps required: ");
  Serial.println(steps);
  // Update current wavelength
  current_wavelength = wavelength;

  Serial.print("New wavelength: ");
  Serial.println(current_wavelength);
  // Testing helper
  Serial.println(1);
  Serial.println();
}
