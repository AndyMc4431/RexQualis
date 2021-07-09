/**********************************************************************
* Filename    : 23.Stepper_Motor.c
* Description : How to use the stepper motor
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim   2019/12/02
**********************************************************************/
#include <stdio.h>
#include <wiringPi.h>

const int motorPins[]={1,4,5,6};    //pins connected to four phase
//1---IN1  4----IN2   5---IN3  6---IN4
const int antiClk[]={0x01,0x02,0x04,0x08};  //right
// 0000 0001   0000  0010   0000 0100  0000 1000
const int clk[]={0x08,0x04,0x02,0x01};   //left
// 0000 1000  0000 0100  0000 0010   0000 0001

void moveSteps(int direction, int steps){
    int step;
    int i=0,j=0;
    for(step=0;step<steps;step++){
        for (j=0;j<4;j++){  //cycle according to power supply order 
        for (i=0;i<4;i++){  //assign to each pin
            if(direction == 1)    //clockwise
                digitalWrite(motorPins[i],antiClk[j] == (1<<i));
            else        //anticlockwise
                digitalWrite(motorPins[i],clk[j] == (1<<i));
        }
        delay(3); //the delay can not be less than 3ms
    }
    }
}
void motorStop(){   //stop rotating
    int i;
    for(i=0;i<4;i++){
        digitalWrite(motorPins[i],LOW); //0000 0000
    }   
}
int main(void){
    int i;
	
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !");
        return 1; 
    }
    for(i=0;i<4;i++){
        pinMode(motorPins[i],OUTPUT);
    } 

    while(1){
        moveSteps(1,512); // clock 512 step
        delay(1000);  //delay 1000
        moveSteps(0,512);  // anticlock 512 step
        delay(1000);  //delay 1000
    }
    return 0;
}

