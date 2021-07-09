/**********************************************************************
* Filename    : 2.RGB-LED
* Description : Make a RGB LED emits various color.
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim    2019/12/02
**********************************************************************/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#define uchar unsigned char
#define LedPinRed    0
#define LedPinGreen  1
#define LedPinBlue   2

void ledInit(void){
    softPwmCreate(LedPinRed,  0, 100);
    softPwmCreate(LedPinGreen,0, 100);
    softPwmCreate(LedPinBlue, 0, 100);
}

void ledColorSet(uchar r_val, uchar g_val, uchar b_val){
    softPwmWrite(LedPinRed,   r_val);
    softPwmWrite(LedPinGreen, g_val);
    softPwmWrite(LedPinBlue,  b_val);
}

int main(void){

    if(wiringPiSetup() == -1){ //when initialize wiring failed, printf messageto screen
        printf("setup wiringPi failed !");
        return 1;
    }

    ledInit();
    while(1){
        printf("Red\n");
        ledColorSet(0xff,0x00,0x00);   //red     
        delay(1000);
        printf("Green\n");
        ledColorSet(0x00,0xff,0x00);   //green
        delay(1000);
        printf("Blue\n");
        ledColorSet(0x00,0x00,0xff);   //blue
        delay(1000);
        printf("Yellow\n");
        ledColorSet(0xff,0xff,0x00);   //yellow
        delay(1000);
        printf("Purple\n");
        ledColorSet(0xff,0x00,0xff);   //purple
        delay(1000);
        printf("Cyan\n");
        ledColorSet(0xc0,0xff,0x3e);   //cyan
        delay(1000);
    }
    return 0;
}
