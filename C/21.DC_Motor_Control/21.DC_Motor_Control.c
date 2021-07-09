/**********************************************************************
* Filename    : 21.DC_Motor_Control.c
* Description : Controlling a motor.
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim    2019/12/02
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define MotorPin1		0  //2A
#define MotorPin2		2  //1A
#define MotorEnable		3  //enable

//main control the L293SD


int main(void){
	int i;
	if(wiringPiSetup() == -1){ //when initialize wiring failed, print message to screen
		printf("setup wiringPi failed !");
		return 1; 
	}
	
	pinMode(MotorPin1, OUTPUT);
	pinMode(MotorPin2, OUTPUT);
	pinMode(MotorEnable, OUTPUT);

	while(1){
		printf("Clockwise\n");
		digitalWrite(MotorEnable, HIGH);
		digitalWrite(MotorPin1, HIGH);//2A is high
		digitalWrite(MotorPin2, LOW);//1A is low
		for(i=0;i<3;i++){
			delay(1000);  //delay time 1000
		}

		printf("Stop\n");
		digitalWrite(MotorEnable, LOW);   // not enable
		for(i=0;i<3;i++){
			delay(1000);  //delay 10000
		}

		printf("Anti-clockwise\n");
		digitalWrite(MotorEnable, HIGH);  //enable
		digitalWrite(MotorPin1, LOW);   //2A is low
		digitalWrite(MotorPin2, HIGH);  //1A is high
		for(i=0;i<3;i++){
			delay(1000);  //delay 1000
		}

		printf("Stop\n");
		digitalWrite(MotorEnable, LOW);  //not enable
		for(i=0;i<3;i++){
			delay(1000);
		}
	}
	return 0;
}

