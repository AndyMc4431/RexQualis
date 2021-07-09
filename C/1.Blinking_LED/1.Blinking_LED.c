/**********************************************************************
* Filename    : 1.Blinking_LED
* Description : Make an led blinking.
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim   2019/12/02
**********************************************************************/
#include <wiringPi.h>  
#include <stdio.h>
#define LedPin      0   //the pin to connect the led
int main(void)
{
    // When initialize wiring failed, print message to screen
    if(wiringPiSetup() == -1){
        printf("setup wiringPi failed !");   //catch error and break
        return 1;
    }
    pinMode(LedPin, OUTPUT);// Set LedPin as output to write value to it.
    while(1){
        // LED on
        digitalWrite(LedPin, LOW);  //write Low to ledPin
        printf("...LED on\n");   //log the led on
        delay(1000); //1000ms delay to blink
        // LED off
        digitalWrite(LedPin, HIGH); //write high to ledPin
        printf("LED off...\n"); //log the led off 
        delay(1000);   //1000ms delay to blink
    }
    return 0;
}

