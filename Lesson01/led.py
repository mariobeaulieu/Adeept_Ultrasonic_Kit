#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
import sys

Led=11
d=0.5

def setup():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup  (Led, GPIO.OUT)
    GPIO.output (Led, GPIO.HIGH)

def loop():
    while True:
        print '...led ON'
        GPIO.output (Led, GPIO.LOW )
        time.sleep(d)
        print '...led OFF'
        GPIO.output (Led, GPIO.HIGH)
        time.sleep(d)

def destroy():
    GPIO.output(Led, GPIO.HIGH)
    GPIO.cleanup()

if __name__ == '__main__':
    if len(sys.argv) > 1:
        try:
            d=float(sys.argv[1])
        except:
            d=0.5
            print '<',sys.argv[1],'> is not a valid value for time delay'
    print 'Using delay of ',d,' seconds'
    setup()
    try:
        loop()
    except KeyboardInterrupt:
        destroy()
