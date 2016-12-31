#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
import sys

BeepPin = 11	# pin11
d=0.1

def setup():
	GPIO.setmode(GPIO.BOARD)        # Numbers pins by physical location
	GPIO.setup(BeepPin, GPIO.OUT)   # Set pin mode as output
	GPIO.output(BeepPin, GPIO.HIGH) # Set pin to high(+3.3V) to off the beep

def loop():
	while True:
		GPIO.output(BeepPin, GPIO.LOW)
		time.sleep(d)
		GPIO.output(BeepPin, GPIO.HIGH)
		time.sleep(d)

def destroy():
	GPIO.output(BeepPin, GPIO.HIGH)	# beep off
	GPIO.cleanup()					 # Release resource

if __name__ == '__main__':	 # Program start from here
	if len(sys.argv) > 1:
		try:
			d=float(sys.argv[1])
		except:
			d=0.1
			print '<',sys.argv[1],'> is not a valid value for time delay'
	print 'Using delay of ',d,' seconds'
	print 'Press Ctrl+C to end the program...'
	setup()
	try:
		loop()
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
		destroy()

