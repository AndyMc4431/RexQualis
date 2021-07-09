/**********************************************************************
* Filename    : 18.Analog_Joystick.c
* Description : read the output data of Joystick and print it to the screen
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim    2019/12/02
**********************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>   //use lib pcf8591

#define PCF       120
#define uchar	unsigned char

int AIN0 = PCF + 0;
int AIN1 = PCF + 1;
int AIN2 = PCF + 2;

//char *state[7] = {"home", "up", "down", "left", "right", "pressed"};

int direction(){
	int x, y, b;
	int tmp;
	x = analogRead(AIN1);
	y = analogRead(AIN0);
	b = analogRead(AIN2);
	if (y == 0)
		tmp = 1;		// up
	if (y == 255)
		tmp = 2;		// down
	
	if (x == 255)
		tmp = 3;		// left
	if (x == 0)
		tmp = 4;		// right

	if (y>=125 && b == 0)
		tmp = 5;		// button preesd
	if (x-125<15 && x-125>-15 && y-125<15 && y-125>-15 && b == 255)
		tmp = 0;		// home position
	
	return tmp;
}

int main (void)
{
	int tmp;
	int status = 0;
	wiringPiSetup ();
	// Setup pcf8591 on base pin 120, and address 0x48
	pcf8591Setup (PCF, 0x48);
	while(1) // loop forever
	{
		tmp = direction();
		if (tmp != status)
		{
			switch(tmp)
			{
				case 0: printf("home\n");break;
				case 1: printf("up\n");break;
				case 2: printf("down\n");break;
				case 3: printf("left\n");break;
				case 4: printf("right\n");break;
				case 5: printf("pressed\n");break;
			}
			status = tmp;
		}
	}
	return 0 ;
}
