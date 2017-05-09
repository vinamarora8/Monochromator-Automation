#!/usr/bin/python2.7

import serial
import sys
from os import system

# make sure the user enters arduino's location as a cl argument
if (sys.argv != 2):
	print("usage: " + sys.argv[0] + " <location of arduino>")

_arduino_location = sys.argv[1]

# TODO: test this past: Compile and Upload to Arduino
system("arduino --upload Control.ino --port " + _arduino_loaction)

# Connect to Arduino using Serial
print "Connecting to Arduino... "
try:
	_arduino = serial.Serial(_arduino_location, 9600)
except serial.serialutil.SerialException:
	print "\nCould not find the given Arduino. Try again"
	print "Exiting..."
	exit()

print "Connected\n"
print "Controlling the Monochromator!\n"
print "List of commands:"
print "[1] Initialize monochromator to 300nm\t: init"
print "[2] Goto wavelength\t\t\t: <wavelength>"
print "[3] Exit Control\t\t\t: exit"

repeat = True

while (repeat):
	a = raw_input("Enter command: ")
	
	if (a == 'init'):
		_arduino.write('701')

	elif (a == 'exit'):
		repeat = False

	else:
		try:
			a = int(a)
			if (a <= 700 && a >= 300):
				_arduino.write(str(a))
		except ValueError:
			print "Invalid command"
