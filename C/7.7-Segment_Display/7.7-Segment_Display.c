/**********************************************************************
* Filename    : 7.7_Segment_Display.c
* Description : Use 74HC595 to control segment.
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim   2019/12/02
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

//use the 74HC595595
#define   SDI   0   //serial data input
#define   RCLK  1   //memory clock input(STCP)
#define   SRCLK 2   //shift register clock input(SHCP)

//A segment code array from 0 to F in Hexadecimal (Common cathode).
unsigned char SegCode[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0011 1111    0000 0110   01011010 ...
//Set ds, st_cp, sh_cp three pins to OUTPUT, and the initial state as 0.
void init(void){  //init all
	pinMode(SDI, OUTPUT); 
	pinMode(RCLK, OUTPUT); 
	pinMode(SRCLK, OUTPUT); 

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}
//To assign 8 bit value to 74HC595’s shift register.
void hc595_shift(unsigned char dat){
	int i;

	for(i=0;i<8;i++){
		digitalWrite(SDI, 0x80 & (dat << i));
        digitalWrite(SRCLK, 1);
		delay(1);
		digitalWrite(SRCLK, 0);
	}

		digitalWrite(RCLK, 1);
		delay(1);
		digitalWrite(RCLK, 0);
}
//In this for loop, we use "%1X" to output i as a hexadecimal number. Apply i to find the corresponding segment code in the SegCode[] array
//employ hc595_shift() to pass the SegCode into 74HC595's shift register.
int main(void){
	int i;

	if(wiringPiSetup() == -1){ //when initialize wiring failed, print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	init();
	while(1){
		for(i=0;i<16;i++){
			printf("Print %1X on Segment\n", i); // %X means hex output 
			hc595_shift(SegCode[i]);
			delay(500);
		}
	}

	return 0;
}

