/**********************************************************************
* Filename    : 19.Photoresistor.c
* Description : Photoresistor control LED
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim    2019/12/02
**********************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>
#include <math.h>

#define		PCF     120  //pcf base
#define		DOpin	0

int main()
{
	int analogVal;
	
	if(wiringPiSetup() == -1){
		printf("setup wiringPi failed !");
		return 1;
	}
	// Setup pcf8591 on base pin 120, and address 0x48
	pcf8591Setup(PCF, 0x48);

	while(1) // loop forever
	{
		analogVal = analogRead(PCF + 0);
		printf("Value: %d\n", analogVal);

		delay (200);
	}
	return 0;
}
