#!/usr/bin/python2.7

import serial
import sys
from os import system

# make sure the user enters arduino's location as a cl argument
if (len(sys.argv) != 2):
	sys.stderr.write("usage: " + sys.argv[0] + " <location of arduino>")
	exit()

_arduino_location = sys.argv[1]

# TODO: test this past: Compile and Upload to Arduino
system("arduino --upload Control.ino --port " + _arduino_location)

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

sys.stdout.write("\n")
while (repeat):
	a = raw_input(">> Enter command: ")

	if (a == 'init'):
		_arduino.write('701')
		print "Initializing..."			
	elif (a == 'exit'):
		repeat = False
		print "Exiting... "	
	else:
		try:
			a = int(a)
			if (a <= 700 and a >= 300):
				_arduino.write(str(a))
				print "Going to : " + str(a) + "nm"
			else:
				print "Unsupported wavelength"
		except ValueError:
			print "Invalid command"
