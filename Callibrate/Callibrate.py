#!/usr/bin/python2.7

# import libraries for : 
# 1) Spectrometer
# 2) Arduino
# 3) Serial Com
import serial

# Get arduino location from the user
_arduino_location = raw_input("Enter the location of your Arduino (/dev/ttyACM0): ") or "/dev/ttyACM0"

# TODO: Compile and Upload to Arduino

# Connect to the Arduino using serial
print "Connecting to Arduino... "
try:
	_arduino = serial.Serial(_arduino_location, 9600)
except serial.serialutil.SerialException:
	print "\nCould not find the given Arduino. Try again"
	print "Exiting..."
	exit()

# Wait for Arduino to be ready (1)
arduino_ready = False
while not arduino_ready:
	_arduino.write("250");
	if (_arduino.read() == '1'):
		arduino_ready = True

print "Connected\n"

# Callibration:

print "Starting Callibration...\n"

while True:
#	current_wav = _spectromter.getWavelength()
	current_wav = int(raw_input("What is the spectrometer showing? "))
	print "Monochromator currently at " + str(current_wav)
	print "Changing... "
	steps = (300.0 - current_wav)*2/7
	steps = int(round(steps))

	if (steps != 0):
		_arduino.write(str(steps))
		
		# Wait for the steps to be made (11)
		done = False
		while not done:
			if (_arduino.read() == '1'):
				done = True

	else:
		_arduino.write(str(0))
		print "System callibrated"
		print "Exiting..."
		exit()
