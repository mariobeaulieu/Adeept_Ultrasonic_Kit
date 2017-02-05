#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

colors = [0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0xFF00FF, 0x00FFFF]
pins = {'pin_R':11, 'pin_G':12, 'pin_B':13}  # pins is a dict

GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
for i in pins:
	GPIO.setup(pins[i], GPIO.OUT)   # Set pins' mode is output
	GPIO.output(pins[i], GPIO.HIGH) # Set pins to high(+3.3V) to off led

p_R = GPIO.PWM(pins['pin_R'], 200)  # set Frequence to 200 Hz
p_G = GPIO.PWM(pins['pin_G'], 200)
p_B = GPIO.PWM(pins['pin_B'], 200)

p_R.start(0)      # Initial duty Cycle = 0(leds off)
p_G.start(0)
p_B.start(0)

def map(x, in_min, in_max, out_min, out_max):
        print "x=",x," min and max in are ",in_min,in_max, " min and max out are ",out_min,out_max
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def setColor(col):   # For example : col = 0x112233
	R_val = (col & 0xff0000) >> 16
	G_val = (col & 0x00ff00) >> 8
	B_val = (col & 0x0000ff) >> 0
	
	R_val = map(R_val, 0, 255, 0, 100)
	G_val = map(G_val, 0, 255, 0, 100)
	B_val = map(B_val, 0, 255, 0, 100)
	
	print "RGB=",R_val,G_val,B_val

	p_R.ChangeDutyCycle(R_val)     # Change duty cycle
	p_G.ChangeDutyCycle(G_val)
	p_B.ChangeDutyCycle(B_val)

for col in colors:
	setColor(col)
	time.sleep(0.5)
v=col
while v != 0:
	v=input( "Entrez une valeur (0 pour terminer): ")
	print "Couleur=",v
	setColor(v);

p_R.stop()
p_G.stop()
p_B.stop()
for i in pins:
	GPIO.output(pins[i], GPIO.HIGH)    # Turn off all leds
GPIO.cleanup()
