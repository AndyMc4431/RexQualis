/**********************************************************************
* Filename    : 24.HC-SR501.c
* Description : Use PIR to sense the movement of pedestrians
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim   2019/12/02
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define ledPin    1  	//define the ledPin
#define sensorPin 0		//define the sensorPin

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}
	
	pinMode(ledPin, OUTPUT);  //control the led
	pinMode(sensorPin, INPUT);  //detect the light

	while(1){
		
		if(digitalRead(sensorPin) == HIGH){ //if read sensor for high level
			digitalWrite(ledPin, HIGH);   //led on
			printf("led on...\n");
		}
		else {				
			digitalWrite(ledPin, LOW);   //led off
			printf("...led off\n");
		}
	}

	return 0;
}

