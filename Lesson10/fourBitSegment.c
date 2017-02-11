/*
* Filename    : fourBitSegment.c
* Description : display 1,2,3,4...
* Website     : www.adeept.com
* E-mail      : support@adeept.com
* Author      : Jason
* Date        : 2015/06/21
*/
#include <wiringPi.h>
#include <stdio.h>

#define   Bit0    8
#define   Bit1    9
#define   Bit2   10
#define   Bit3   11

unsigned char const SegCode[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x79,0x71,0x54};

unsigned char DatBuf[4] = {0,0,0,0};

int cnt = 60;

void sysInit(void)
{
	int i;

	for(i = 0; i < 12; i++){
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}	
}

void do_cnt(void)
{
	DatBuf[0] = SegCode[cnt % 10];
	DatBuf[1] = SegCode[cnt % 100 / 10];
	DatBuf[2] = SegCode[cnt % 1000 / 100];
	DatBuf[3] = SegCode[cnt / 1000];
}

void display(void)
{
	int i;
	// The loop goes 250 times and has 4 ms delays in it for a total of 1 sec
	for(i = 0;i < 250; i++){
		digitalWrite(Bit0, 0);
		digitalWrite(Bit1, 1);
		digitalWrite(Bit2, 1);
		digitalWrite(Bit3, 1);
		digitalWriteByte(DatBuf[0]);
		delay(1);
		digitalWrite(Bit0, 1);

		if (cnt>9 ) {
			digitalWrite(Bit1, 0);
			digitalWriteByte(DatBuf[1]);
			delay(1);
			digitalWrite(Bit1, 1);
			if (cnt>99 ) {
				digitalWrite(Bit2, 0);
				digitalWriteByte(DatBuf[2]);
				delay(1);
				digitalWrite(Bit2, 1);
				if (cnt>999 ) {
					digitalWrite(Bit3, 0);
					digitalWriteByte(DatBuf[3]);
					delay(1);
					digitalWrite(Bit3, 1);
				} else delay(1);
			} else delay(2);
		} else delay(3);
	}
}
void bang(void)
{
	int i;
	// The loop goes 250 times and has 4 ms delays in it for a total of 1 sec
	for(i = 0;i < 250; i++){
		digitalWrite(Bit0, 0);
		digitalWrite(Bit1, 1);
		digitalWrite(Bit2, 1);
		digitalWrite(Bit3, 1);
		digitalWriteByte(SegCode[9]);
		delay(1);
		digitalWrite(Bit0, 1);
		digitalWrite(Bit1, 0);
		digitalWriteByte(SegCode[16]);
		delay(1);
		digitalWrite(Bit1, 1);
		digitalWrite(Bit2, 0);
		digitalWriteByte(SegCode[10]);
		delay(1);
		digitalWrite(Bit2, 1);
		digitalWrite(Bit3, 0);
		digitalWriteByte(SegCode[11]);
		delay(1);
		digitalWrite(Bit3, 1);
	}
}

int main(int argc, char* argv[])
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
		printf("setup wiringPi failed !\n");
		return -1; 
	}

	cnt=60;
	if ( argc >1 ) {
		cnt = atoi(argv[1]);
	}
	printf("Countdown from %d seconds\n", cnt);
	sysInit();

	while(cnt-- > 0) {
		do_cnt();
		display();
	}
	bang();
	delay(200);
	bang();
	delay(200);
	bang();
	return 0;
}
