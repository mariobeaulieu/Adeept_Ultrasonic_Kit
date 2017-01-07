/*
* File name   : btnAndLed.c
* Description : Toggle a led by button.
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Modified by : Mario
*               Added thread to return the board to initial condition and stop everything if ENTER is pressed
* Date        : 2017/01/03
*/
#include <wiringPi.h>
#include <stdio.h>
#include <pthread.h>

#define LedPin    0
#define ButtonPin 1

int status = 1;

/* This is the Interrupt Service Routine that is called when a falling edge is detected */
void myISR(void)
{
	status = !status;	
}

// Global variable enter.
// The pthread will change its value when ENTER will be pressed
int enter=0;

/***********************************************
* Function waitForEnter
*
* This function waits for key Enter to be 
* pressed.
* When pressed, it changes the value of its
* parameter and then exit.
***********************************************/
void *waitForEnter()
{
	char c;

	printf("Press <ENTER> to terminate\n");
	scanf("%c",&c);
	printf("Closing thread\n");

	enter++;

	pthread_exit(0);
}
	
int main(void)
{
	int rc;
	int prevStatus=2;
	pthread_t waitThread;

	if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}
	
	// Setup pins for LED as output and button as input
	pinMode(LedPin, OUTPUT); 
	pinMode(ButtonPin, INPUT);

	// Button is 3.3V when not pressed. Pressing it brings tension to 0V
	pullUpDnControl(ButtonPin, PUD_UP);
	
	// We want to detect falling edge
	if(wiringPiISR(ButtonPin, INT_EDGE_FALLING, myISR) < 0){
		printf("ISR setup error!\n");
		return -1;
	}

	// Start the thread that monitors the keyboard for ENTER
	// That thread will change t for 0 when ENTER is pressed
	rc = pthread_create( &waitThread, NULL, waitForEnter, NULL);
	if ( rc ) {
		printf("Error %d when creating the thread to read keyboard\n", rc);
		return -1;
	}

	/* The pthread will change the value of myArgs.v when ENTER will e pressed */
	while(enter == 0){
		if ( prevStatus != status ) {
			digitalWrite(LedPin, status);
			prevStatus = status;
			printf ("Status is %d\n", status);
		}
	}

	// ENTER has been pressed
	printf("Closing program\n");

	// Set LED to input
	digitalWrite(LedPin, LOW );
	pinMode(LedPin, INPUT);

	// Make sure that thread is exited
	pthread_join(waitThread, NULL);

	return 0;
}
