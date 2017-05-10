import seabreeze.spectrometers as sb

print "Finding spectrometers... "
devices = sb.list_devices()

## If no spectrometer is found
while len(devices) == 0 :
	inp = raw_input("No spectrometer detected. Try again? (Y/N) : ")

	if (inp == "N" or inp == "n"): 
		exit()
	else:
		devices = sb.list_devices()

print ""

## Establishing connection
spec = sb.Spectrometer(devices[0])
print "Connection to " + str(devices[0]) + " established"
spec.integration_time_micros(10000000)

def max_wavelength():

	max_intensity = 0;
	max_wavelength = 0;
	
	wavelengths = spec.wavelengths()
	intensities = spec.intensities()
	
	data = zip(wavelengths, intensities)
	
	for (x,y) in data:
		if (x >= 300 and x <= 700):
			if (y > max_intensity):
				max_intensity = y;
				max_wavelength = x;

	return max_wavelength;


def max_avg_wavelength():
	
	max_avg = 0;

	for i in range(0, 10):
		max_avg = max_avg + max_wavelength()

	max_avg = max_avg/10

	return max_avg
