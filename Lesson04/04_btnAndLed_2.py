#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

LedPin = 11    # pin11 --- led
BtnPin = 12    # pin12 --- button

Led_status = 1
count=0

last_time=0 # Last time the swLed was called
delta=2.0   # Delay we must wait for debouncing
            # If 2 clicks happen within that time, the second is ignored

def setup():
	GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
	GPIO.setup(LedPin, GPIO.OUT)   # Set LedPin's mode is output
	GPIO.setup(BtnPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)    # Set BtnPin's mode is input, and pull up to high level(3.3V)
	GPIO.output(LedPin, GPIO.HIGH) # Set LedPin high(+3.3V) to make led off

def swLed(ev=None):
	global Led_status,count,last_time,delta
	time_now=time.time()
	# If less than delta time has elapsed, don't change status
	if last_time + delta < time_now:
		last_time = time_now
		Led_status = not Led_status
		GPIO.output(LedPin, Led_status)  # switch led status(on-->off; off-->on)
		count+=1
		if Led_status == 1:
			print count,'... led off'
		else:
			print count, '...led on'

def loop():
	GPIO.add_event_detect(BtnPin, GPIO.FALLING, callback=swLed) # wait for falling
	while True:
		pass   # Don't do anything

def destroy():
	GPIO.output(LedPin, GPIO.HIGH)     # led off
	GPIO.cleanup()                     # Release resource

if __name__ == '__main__':     # Program start from here
	setup()
	try:
		loop()
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
		destroy()

