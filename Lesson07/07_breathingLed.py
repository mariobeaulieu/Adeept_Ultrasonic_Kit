#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
import sys
import tty

LedPin = 12

GPIO.setmode(GPIO.BOARD)	 # Numbers pins by physical location
GPIO.setup(LedPin, GPIO.OUT)	 # Set pin mode as output
GPIO.output(LedPin, GPIO.LOW)    # Set pin to low(0V)

d=50

if len(sys.argv) > 1:
	try:
		d=int(sys.argv[1])
	except:
		d=50
		print '<',sys.argv[1],'> is not a valid value for freq (use 1-10000)'
print 'Using frequency of ',d,' hertz'
p = GPIO.PWM(LedPin, d)		 # set Frequece to 1KHz
p.start(0)			 # Start PWM output, Duty Cycle = 0

try:
	while True:
		for dc in range(0, 101, 4):   # Increase duty cycle: 0~100
			p.ChangeDutyCycle(dc)	 # Change duty cycle
			print 'Duty cycle is ',dc
			raw_input('Press enter')
		for dc in range(100, -1, -4): # Decrease duty cycle: 100~0
			p.ChangeDutyCycle(dc)
			print 'Duty cycle is ',dc
			raw_input('Press enter')
except KeyboardInterrupt:
	p.stop()
	GPIO.output(LedPin, GPIO.HIGH)	# turn off all leds
	GPIO.cleanup()

