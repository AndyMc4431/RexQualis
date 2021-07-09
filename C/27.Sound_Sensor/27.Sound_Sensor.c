/**********************************************************************
* Filename    : 27.Sound_Sensor.c
* Description : 
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim    2019/12/02
**********************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>  //pcf8591 lib

#define PCF       120

int main (void)
{
	int value;
	int count = 0;
	wiringPiSetup ();
	// Setup pcf8591 on base pin 120, and address 0x48
	pcf8591Setup (PCF, 0x48);
	while(1) // loop forever
	{
		value = analogRead  (PCF + 0);
		//printf("%d\n", value);
		if (value < 50){
			count++;
			printf("Voice In!!  %d\n", count);
		}
	}
	return 0;
}
