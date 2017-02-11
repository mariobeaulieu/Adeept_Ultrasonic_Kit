#!/usr/bin/env python  

import RPi.GPIO as GPIO  
import time  

BIT0 = 3   
BIT1 = 5  
BIT2 = 24  
BIT3 = 26  

segCode = [0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x79,0x71,0x80]
pins = [11,12,13,15,16,18,22,7,3,5,24,26]  
bits = [BIT0, BIT1, BIT2, BIT3]  

def print_msg():  
	print 'Program is running...'  
	print 'Please press Ctrl+C to end the program...'  

def digitalWriteByte(val):  
	GPIO.output(11, val & (0x01 << 0))  
	GPIO.output(12, val & (0x01 << 1))  
	GPIO.output(13, val & (0x01 << 2))  
	GPIO.output(15, val & (0x01 << 3))  
	GPIO.output(16, val & (0x01 << 4))  
	GPIO.output(18, val & (0x01 << 5))  
	GPIO.output(22, val & (0x01 << 6))  
	GPIO.output(7,  val & (0x01 << 7))  

def display_1():  
	GPIO.output(BIT0, GPIO.LOW)   
	for i in range(10):  
		digitalWriteByte(segCode[i])  
		time.sleep(0.5)  
	GPIO.output(BIT0, GPIO.HIGH)   

def display_2():  
	for bit in bits:
		GPIO.output(bit, GPIO.LOW)   
	for i in range(10):  
		digitalWriteByte(segCode[i])  
		time.sleep(0.5)  
	for bit in bits:
		GPIO.output(bit, GPIO.HIGH)   

def display_3(num):  
	b0 = num % 10  
	b1 = num % 100 / 10   
	b2 = num % 1000 / 100  
	b3 = num / 1000

	GPIO.output(BIT0, GPIO.LOW)  
	digitalWriteByte(segCode[b0])  
	time.sleep(0.005)  
	GPIO.output(BIT0, GPIO.HIGH)   
	if num>9:
		GPIO.output(BIT1, GPIO.LOW)  
		digitalWriteByte(segCode[b1])  
		time.sleep(0.005)  
		GPIO.output(BIT1, GPIO.HIGH)  
	if num>99:
		GPIO.output(BIT2, GPIO.LOW)  
		digitalWriteByte(segCode[b2])  
		time.sleep(0.005)  
		GPIO.output(BIT2, GPIO.HIGH)   
	if num>999:
		GPIO.output(BIT3, GPIO.LOW)  
		digitalWriteByte(segCode[b3])  
		time.sleep(0.005)  
 		GPIO.output(BIT3, GPIO.HIGH)   

def display_hex(num):  
	b0 = num % 16  
	b1 = num % 256 / 16   
	b2 = num % 4096 / 256  
	b3 = num % 65536 / 4096

	GPIO.output(BIT0, GPIO.LOW)  
	digitalWriteByte(segCode[b0])  
	time.sleep(0.005)  
	GPIO.output(BIT0, GPIO.HIGH)   
	if num>0xf:
		GPIO.output(BIT1, GPIO.LOW)  
		digitalWriteByte(segCode[b1])  
		time.sleep(0.005)  
		GPIO.output(BIT1, GPIO.HIGH)  
	if num>0xff:
		GPIO.output(BIT2, GPIO.LOW)  
		digitalWriteByte(segCode[b2])  
		time.sleep(0.005)  
		GPIO.output(BIT2, GPIO.HIGH)   
	if num>0xfff:
		GPIO.output(BIT3, GPIO.LOW)  
		digitalWriteByte(segCode[b3])  
		time.sleep(0.005)  
 		GPIO.output(BIT3, GPIO.HIGH)   

def setup():  
	GPIO.setmode(GPIO.BOARD)    #Number GPIOs by its physical location  
	for pin in pins:  
		GPIO.setup(pin, GPIO.OUT)    #set all pins' mode is output  
		GPIO.output(pin, GPIO.HIGH)  #set all pins are high level(3.3V)  

def loop():  
	print_msg()  
	display_1()  
	time.sleep(1)  
	display_2()  
	time.sleep(1)  

	while True:
		tmp = int(raw_input('Please input a num(0~9999):'))  
		if tmp<0 or tmp>9999: break
		for i in range(500):  
			display_3(tmp)  
		time.sleep(1)  

	while True:
		tmp = int(raw_input('Please input a HEX num (0~ffff):'),16)  
		if tmp<0 or tmp>0xffff: break
		for i in range(500):  
			display_hex(tmp)  
		time.sleep(1)  

	destroy()

def destroy():   #When program ending, the function is executed.   
	for pin in pins:    
		GPIO.output(pin, GPIO.LOW) #set all pins are low level(0V)   
		GPIO.setup(pin, GPIO.IN)   #set all pins' mode is input  

if __name__ == '__main__': #Program starting from here   
	setup()   
	try:  
		loop()    
	except KeyboardInterrupt:    
		destroy()    
