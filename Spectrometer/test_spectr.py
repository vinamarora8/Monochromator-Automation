#!/usr/bin/python2.7

from spectrometer import *

ans =  'y'

while (ans != 'N' and ans != 'n'):
	print max_wavelength()
	ans = raw_input("Again? (Y/N) ")
