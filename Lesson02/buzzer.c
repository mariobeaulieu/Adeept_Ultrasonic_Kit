///////////////////////////////////////////////
// To compile: 
// gcc buzzer.c -l wiringPi -l pthread -o buzzer
//
///////////////////////////////////////////////
/*
* File name   : buzzer.c
* Description : Make an active buzzer sound.
* Author      : Mario Beaulieu
* Date        : 2016/12/31
*/
#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>

#define BeepPin 0

void *doBeeps(void* t)
{
	int beepLength;

	beepLength = (int)t;
	while(1){
		digitalWrite(BeepPin, LOW);  //beep on
		delay(beepLength);           //delay
		digitalWrite(BeepPin, HIGH); //beep off
		delay(beepLength);           //delay
	}
}

int main(int argc, char* argv[])
{
	pthread_t beepThread;
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
	
	pinMode(BeepPin, OUTPUT);   //set GPIO0 output
	rc = pthread_create( &beepThread, NULL, doBeeps, (void*)d);
	if (rc) {
		printf("Error %d when creating thread\n",rc);
		return -1;
	}

	printf("Press ENTER when done...");
	scanf("%c", &c);

	rc=pthread_cancel(beepThread);
	digitalWrite(BeepPin, HIGH); //beep off
	pinMode(BeepPin, INPUT);     //set GPIO0 input
	return 0;
}

