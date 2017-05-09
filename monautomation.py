#!/usr/bin/python2.7

import sys
from os import system

if (len(sys.argv) == 2):
	_arduino_location = sys.argv[1]
else:
	_arduino_location = raw_input("Enter location of your arduino (/dev/ttyACM0): ") or "/dev/ttyACM0"

repeat = True

while (repeat):
	print "\nAvailable actions: "
	print "[1] Control\t\t: 1"
	print "[2] Callibrate\t\t: 2"
	print "[3] Exit\t\t: exit\n"

	a = raw_input(">> Select your action: ")

	if (a == "1"):
		system("Control/Control.py " + _arduino_location)

	elif (a == "2"):
		system("Callibrate/Callibrate.py " + _arduino_location)
	
	elif (a == "exit"):
		print "Exiting..."
		repeat = False
	
	else:
		print "Invalid action"
