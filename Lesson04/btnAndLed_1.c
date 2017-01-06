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

/* The structure used for the argument contains only 1 integer.
 * I had to use a structure in order to have the thead return a value
 * to its calling program.
 */
struct args {
	int v;
};

/***********************************************
* Function waitForEnter
*
* This function waits for key Enter to be 
* pressed.
* When pressed, it changes the value of its
* parameter and then exit.
* To be able to change the value of its parameter,
* I had to use a structure for it.
* pthreads require parameter to be a void* pointer
* Passing a structure allows me to change the value in
* the structure. 
***********************************************/
void *waitForEnter(void* a)
{
	char c;
	struct args *myArgs;
	myArgs = (struct args*)a;

	printf("Press <ENTER> to terminate\n");
	scanf("%c",&c);
	printf("Closing thread\n");

	printf("myArgs->v=%d\n",myArgs->v);
	myArgs->v=0;
	printf("myArgs->v=%d\n",myArgs->v);

	pthread_exit(0);
}
	
int main(void)
{
	int rc;
	struct args myArgs;
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
	myArgs.v=1;
	rc = pthread_create( &waitThread, NULL, waitForEnter, (void*)(&myArgs));
	if ( rc ) {
		printf("Error %d when creating the thread to read keyboard\n", rc);
		return -1;
	}

	/* The pthread will change the value of myArgs.v when ENTER will e pressed */
	while(myArgs.v > 0){
		if ( prevStatus != status ) {
			digitalWrite(LedPin, status);
			prevStatus = status;
			printf ("Status is %d\n", status);
		}
	}

	// ENTER has been pressed and value of t has changed
	printf("Closing program\n");

	// Set LED to input
	digitalWrite(LedPin, LOW );
	pinMode(LedPin, INPUT);

	// Make sure that thread is exited
	pthread_join(waitThread, (void**)&rc);

	return 0;
}
