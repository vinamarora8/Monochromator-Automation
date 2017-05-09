import seabreeze.spectrometers as sb

###				Connection Handling				###

## Find connected spectrometers
print "Finding connected spectrometers... "
devices = sb.list_devices()

## Handler
## If no spectrometer is found
while len(devices) == 0 :
	inp = raw_input("No spectrometer detected. Try again? (Y/N) : ")

	if a == "N" or a == "n" : 
		exit()
	else:
		devices = sb.list_devices()

print ""

## Establishing connection
## Assuming only 1 spectrometer is connected at a time
spec = sb.Spectrometer(devices[0])
print "Connection to " + str(devices[0]) + " established"
spec.integration_time_micros(int(raw_input("Integration time: ")))

## Store wavelength array, useful for future
wav = spec.wavelengths()

###			   Useful Basic Functions			###

## Returns wavelength array
def get_wavelengths() :
	return spec.wavelengths()

## Returns intensities array
def get_instensities() :
	return spec.intesities()

## Returns index for wavelength = 300
def get_300_index(wavelengths = wav):
	for i in range(0, len(wavelengths)):
		if wavelengths[i] >= 300:
			return i

## Returns index for wavelength = 800
def get_800_index(wavelengths = wav):
	for i in range(len(wavelengths)-1, 0, -1):
		if wavelengths[i] <= 800:
			return i	

## Strips wavelength array to visible region
def strip_wavelengths_vis(wavelengths = wav):
	return wavelengths[get_300_index(wavelengths): get_800_index(wavelengths) + 1]

## To reduce calculating stripped wavelength array every time query is made
strip_wav = strip_wavelengths_vis()

## Strips intesities array to visible region
def strip_intesities_visible(intensities, wavelengths = wav):
	return intesities[get_300_index(wavelengths): get_800_index(wavelengths) + 1]

## Returns stripped wavelength array
def get_stripped_wavelengths():
	return strip_wavelength_vis(get_wavelengths())

## Returns stripped intensities array
def get_stripped_intesities():
	return strip_intensities_vis(get_intesities(), get_wavelengths())



###			   Useful Advanced Functions			###

## Returns intesities calculated n times and averaged
def get_avg_vis_intesities(n = 10):
	ans = [0]*len(strip_wavelengths_vis())
	for i in range(0, n):
		ans = [x+y for x,y in zip(ans, get_stripped_intesities())]
	return map(lambda x: x/n, ans)

## Returns wavelength with maximum intesity
def get_strongest_wavelength(intesities, wavelength = strip_wav):
	max_index = 0
	for i in range(0, len(intesities)):
		if intensities[i] >= intensities[max_index]:
			max_index = i
	return wavelengths[max_index]

## Returns wavelength with maximum average intesity
def get_avg_strongest_wavelength_vis(n = 10):
	return get_strongest_wavelength(get_avg_vis_intesities(n))
