/*
* File name   : breathingLed.c
* Description : control the brightness of led by PWM.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Modified by : Mario
* Date        : 2017/01/15
*/

#include <wiringPi.h>
#include <stdio.h>

#define LedPin    1

int main(void)
{
	int i;

	if(wiringPiSetup() < 0){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !\n");
		return -1;
	}

	softPwmCreate(LedPin,0, 100);  

	while(1){
		for(i=0;i<100;i+=4){
			printf("i=%d\n",i);
			softPwmWrite(LedPin, i);
			delay(200);
		}
		delay(1000);
		for(i=100;i>=0;i-=4){
			printf("i=%d\n",i);
			softPwmWrite(LedPin, i);
			delay(200);
		}
		delay(1000);
	}

	return 0;
}
