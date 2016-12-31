#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//compiles even if pthread isn't included!
#include <pthread.h>

///////////////////////////////////////////////
// To compile: 
// gcc led.c -l wiringPi -l pthread -o led
//
///////////////////////////////////////////////

#define LED 0 //wiringPi GPIO0, pin 11

void * doLeds(void* t) {
	int d=(int)t;

	pinMode(LED, OUTPUT);

	while(1) {
		digitalWrite(LED, LOW ); // LED ON
		printf("LED ON ...\n");
		delay(d);
		digitalWrite(LED, HIGH); // LED OFF
		printf("... LED OFF\n");
		delay(d);
	}
}

int main(int argc, char* argv[]) {
	pthread_t ledThread;
	int rc;
	int d=100;
	char c;

	if (argc > 1) {
		printf("There are %d arguments\n", argc);
		printf("Using <%s> as delay (in ms)", argv[1]);
		d=atoi(argv[1]);
	}

	if(wiringPiSetup() == -1){ //when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed !");
		return -1; 
	}
	
	pinMode(LED, OUTPUT);   //set GPIO0 output
	rc = pthread_create( &ledThread, NULL, doLeds, (void*)d);
	if (rc) {
		printf("Error %d when creating thread\n",rc);
		return -1;
	}

	printf("Press ENTER when done...\n");
	scanf("%c", &c);

	rc=pthread_cancel(ledThread);
	digitalWrite(LED, HIGH); // led off
	pinMode(LED, INPUT);     // set GPIO0 input
	return 0;
}
