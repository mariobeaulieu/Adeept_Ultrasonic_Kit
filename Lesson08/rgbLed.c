/*
 * File name   : rgbLed.c
 * Description : control a rgb led 
 * Website     : www.adeept.com
 * E-mail      : support@adeept.com
 * Author      : Jason
 * Date        : 2015/05/26
 */
#include <wiringPi.h>  
#include <softPwm.h>  
#include <stdio.h>  
#include <sys/ioctl.h>
#include <errno.h>

#define LedPinRed    0  
#define LedPinGreen  1  
#define LedPinBlue   2  

int kbhit()
{
 int i;
 ioctl(0, FIONREAD, &i);
 return i; /* return a count of chars available to read */
}

const int colors[] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00, 0x00FFFF, 0xFF00FF, 0xFFFFFF, 0x9400D3};  

int map(int x, int in_min, int in_max, int out_min, int out_max)     
{  
	return (x -in_min) * (out_max - out_min) / (in_max - in_min) + out_min;  
}  

void ledInit(void)  
{  
	softPwmCreate(LedPinRed,  0, 100);  //create a soft pwm, original duty cycle is 0Hz, range is 0~100   
	softPwmCreate(LedPinGreen,0, 100);  
	softPwmCreate(LedPinBlue, 0, 100);  
}  

void ledColorSet(int color)        //set color, for example: 0xde3f47  
{  
	int r_val, g_val, b_val;  

	r_val = (color & 0xFF0000) >> 16;  //get red value  
	g_val = (color & 0x00FF00) >> 8;   //get green value  
	b_val = (color & 0x0000FF) >> 0;   //get blue value  

	r_val = map(r_val, 0, 255, 0, 100);    //change a num(0~255) to 0~100  
	g_val = map(g_val, 0, 255, 0, 100);  
	b_val = map(b_val, 0, 255, 0, 100);  

	softPwmWrite(LedPinRed,   100 - r_val);  //change duty cycle  
	softPwmWrite(LedPinGreen, 100 - g_val);  
	softPwmWrite(LedPinBlue,  100 - b_val);  
}  

int main(void)  
{  
	int r,g,b;  

	if(wiringPiSetup() < 0){ //when initialize wiringPi failed, print message to screen  
		printf("setup wiringPi failed !\n");  
		return -1;   
	}  

	ledInit();  
	printf("Press any key to terminate\n");
	while(1){
		printf("Looping...\n");  
		for( r = 0; r <= 100; r+=10 ) {
			printf("r=%d\n", r);
			for ( g=0; g<=100;g+=10 ) {
				for ( b=0;b<=100;b+=10 ) {
					softPwmWrite(LedPinRed,   100-r);  //change duty cycle  
					softPwmWrite(LedPinGreen, 100-g);  
					softPwmWrite(LedPinBlue,  100-b);  
					delay(10);
				}
			}
		}  
		if ( kbhit() ) {
			printf("Break!\n");
			break;
		}
	}  
	softPwmWrite(LedPinRed,   100);
	softPwmWrite(LedPinGreen, 100);  
	softPwmWrite(LedPinBlue,  100);
	printf("Error code is %d\n",errno);  
	delay(500);
	return 0;  
}  
