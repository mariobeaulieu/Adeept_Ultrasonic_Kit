#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
import sys

TiltPin = 12
LedPin  = 11

Led_status = 1

def setup():
	GPIO.setmode(GPIO.BOARD)       # Numbers pins by physical location
	GPIO.setup(LedPin, GPIO.OUT)   # Set pin mode as output
	GPIO.setup(TiltPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
	GPIO.output(LedPin, GPIO.HIGH) # Set pin to high(+3.3V) to off the led

def swLed(ev=None):
	global Led_status
	Led_status = not Led_status
	GPIO.output(LedPin, Led_status)  # switch led status(on-->off; off-->on)
	if Led_status == 1:
		print 'led off...'
	else:
		print '...led on'
	# Debounce delay
	time.sleep( 1.0 )

def loop():
	GPIO.add_event_detect(TiltPin, GPIO.FALLING, callback=swLed) # wait for falling
	while True:
		pass   # Don't do anything

def testPin():
	prev=1
	while True:
		curr = GPIO.input(TiltPin)
		if curr != prev:
			print "State is ", curr
			swLed()
			prev = curr

def destroy():
	GPIO.output(LedPin, GPIO.HIGH)     # led off
	GPIO.cleanup()                     # Release resource

if __name__ == '__main__':     # Program start from here
	setup()
	mode = raw_input('Mode: e=edge, v=value: ')
	try:
		if mode == 'e':
			print 'Using edge detection mode'
			loop()
		else:
			print 'Using level value mode'
			testPin()
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, function destroy() is called.
		destroy()

