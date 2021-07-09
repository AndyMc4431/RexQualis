/**********************************************************************
* Filename    : 10.Tilt_Ball_Swith.c
* Description : learn how to use a tilt ball switch in order to detect small angle of inclination.
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim    2019/12/02
**********************************************************************/

#include <wiringPi.h>
#include <stdio.h>

#define TiltPin		0  //wiringpi 0
#define Gpin		2	//wiringpi 2
#define Rpin		3   //wiringpi 3

void LED(char* color)
{
	pinMode(Gpin, OUTPUT);
	pinMode(Rpin, OUTPUT);
	if (color == "RED")
	{
		digitalWrite(Rpin, HIGH);
		digitalWrite(Gpin, LOW);
	}
	else if (color == "GREEN")
	{
		digitalWrite(Rpin, LOW);
		digitalWrite(Gpin, HIGH);
	}
	else
		printf("LED Error");
}

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	pinMode(TiltPin, INPUT);
	LED("GREEN");
	
	while(1){                //loop to observe the Tiltpin
		if(0 == digitalRead(TiltPin)){
			delay(10);
			if(0 == digitalRead(TiltPin)){
				LED("RED");
				printf("Tilt!\n");
			}
		}
		else if(1 == digitalRead(TiltPin)){
			delay(10);
			if(1 == digitalRead(TiltPin)){
				LED("GREEN");
			}
		}
	}
	return 0;
}
