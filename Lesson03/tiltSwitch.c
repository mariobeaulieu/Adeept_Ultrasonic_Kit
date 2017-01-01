/*
* File name   : tiltSwitch.c
* Description : Toggle the status of LED by tilt switch.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date	: 2015/05/26
*/
#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>

#define  LedPin    0
#define  TiltPin   1

void *doTilts() {
	int previous=2;
	int current;

	while(1){
		current=digitalRead(TiltPin);
		if(current == 0) digitalWrite(LedPin, LOW);   //led on
		else             digitalWrite(LedPin, HIGH);  //led off

		if (current!=previous) {
			printf("Tilt is %d...\n", current);
			previous=current;
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	pthread_t tiltThread;
	int rc;
	char c;

	if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !");
		return -1; 
	}
	
	pinMode(LedPin, OUTPUT);
	pinMode(TiltPin, INPUT);

	rc = pthread_create( &tiltThread, NULL, doTilts, NULL);
	if (rc) {
		printf("Error %d when creating thread\n",rc);
		return -1;
	}

	printf("Press ENTER when done...");
	scanf("%c", &c);

	rc=pthread_cancel(tiltThread);
	digitalWrite(LedPin, LOW ); //beep off
	pinMode(LedPin, INPUT);     //set GPIO0 input

	return 0;
}
