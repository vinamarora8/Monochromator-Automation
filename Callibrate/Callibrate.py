#!/usr/bin/python2.7

import serial
from spectr import *
from os import system
import sys

# make sure the user enters arduino's location as a cl argument
if (len(sys.argv) != 2):
	sys.stderr.write("usage: " + sys.argv[0] + " <location of arduino>")
	exit()

_arduino_location = sys.argv[1]

# TODO: test this part: Compile and Upload to Arduino
system("arduino --upload Callibrate.ino --port " + _arduino_location)

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
	current_wav = get_avg_strongest_wavelength_vis(10)
	#current_wav = int(raw_input("What is the spectrometer showing? "))
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
		print "Exiting Callibrate..."
		exit()
