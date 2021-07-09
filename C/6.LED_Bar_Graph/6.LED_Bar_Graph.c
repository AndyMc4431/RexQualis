/**********************************************************************
* Filename    : 6.Led_Bar_Graph.c
* Description : The LEDs on the LED bar lit one by one from left to right, and then lit one by one from right to left..
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim    2019/12/02
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
int pins[10] = {0,1,2,3,4,5,6,8,9,10};
int main(void)
{
    int i;
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !");
        return 1;
    }
    for(i=0;i<=10;i++){       //make led pins' mode is output
        pinMode(pins[i], OUTPUT);
    }
    while(1){
        for(i=0;i<=10;i++){   //make led on from left to right
            if(i==7){continue;} //skip pin 7
            digitalWrite(i, LOW);
            delay(100);
            digitalWrite(i, HIGH);
        }
        for(i=10;i>-1;i--){   //make led on from right to left
            if(i==7){continue;}
            digitalWrite(i, LOW);
            delay(100);
            digitalWrite(i, HIGH);
        }
    }
    return 0;
}