#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
import sys

d=0.1
trainLength=8
leds=[11,12,13,15,16,18,22,7,29,31,33,35,37,32,36,38]
numLeds=len(leds)

def setup():
    GPIO.setmode(GPIO.BOARD)
    print "There are ",numLeds," leds"
    for i in leds:
        print "Setting channel ",i
        GPIO.setup  (i, GPIO.OUT)
        GPIO.output (i, GPIO.LOW)

def loop():
    i=0
    j=trainLength
    while True:
        GPIO.output (leds[i], GPIO.LOW )
        i += 1
        if i >= numLeds: i = 0
        GPIO.output (leds[j], GPIO.HIGH)
        j += 1
        if j >= numLeds: j = 0
        time.sleep(d)

def destroy():
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
