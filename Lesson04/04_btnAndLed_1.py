#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

LedPin = 11    # pin11 --- led
BtnPin = 12    # pin12 --- button

def setup():
	GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
	GPIO.setup(LedPin, GPIO.OUT)   # Set LedPin's mode is output
	GPIO.setup(BtnPin, GPIO.IN, pull_up_down=GPIO.PUD_UP  )    # Set BtnPin's mode is input, and pull up to high level(3.3V)
	GPIO.output(LedPin, GPIO.HIGH) # Set LedPin high(+3.3V) to make led off

def loop():
	#prev is the previous state
	#2 in an invalid state, so state!=prev is true the first loop
	prev=2
	while True:
		state=GPIO.input(BtnPin)
		# We change the state of the pin only if button changed.
		# This is mostly to avoid filling screen with ...led...on/off
		if state != prev:
			# The delay is for debouncing
			time.sleep(0.1)
			prev=state
			if state == GPIO.LOW: # Check whether the button is pressed or not.
				print '...led on'
				GPIO.output(LedPin, GPIO.LOW)  # led on
			else:
				print 'led off...'
				GPIO.output(LedPin, GPIO.HIGH) # led off

def destroy():
	GPIO.output(LedPin, GPIO.HIGH)     # led off
	GPIO.cleanup()                     # Release resource

if __name__ == '__main__':     # Program start from here
	setup()
	try:
		loop()
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
		destroy()
