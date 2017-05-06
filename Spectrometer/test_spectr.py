#!/usr/bin/python2.7

from spectr import *

ans =  'y'

while (ans != 'N' or ans != 'n'):
	print get_avg_strongest_wavelength_vis(10)
	ans = raw_input("Again? (Y/N) ")
