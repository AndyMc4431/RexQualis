/**********************************************************************
* Filename    : 11.Ultrasonic_Sensor.c
* Description : Get distance from UltrasonicRanging
* Author      : Robot
* E-mail      : support@rexuqalis.com
* website     : www.rexqualis.com
* Update      : Tim   2019/12/02
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>  //provide timer

#define Trig    4
#define Echo    5
void ultraInit(void)
{
    pinMode(Echo, INPUT);   //define the 4 ---input
    pinMode(Trig, OUTPUT);   //define the 5 ----output
}

float disMeasure(void)
{
    struct timeval tv1;
    struct timeval tv2;
    long time1, time2;
   float dis;

    digitalWrite(Trig, LOW);
    delayMicroseconds(2);   //2ms to pwm

    digitalWrite(Trig, HIGH); 
    delayMicroseconds(10);      
    digitalWrite(Trig, LOW);// _'_ to triger to get out
                                
    while(!(digitalRead(Echo) == 1));   
    gettimeofday(&tv1, NULL);  //transform to time          

    while(!(digitalRead(Echo) == 0));   
    gettimeofday(&tv2, NULL);   //transform to time     

    time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;   //get the microsecond
    time2  = tv2.tv_sec * 1000000 + tv2.tv_usec;  //get the microsecond

    dis = (float)(time2 - time1) / 1000000 * 34000 / 2;   //the voice speed * timer 

    return dis;
}

int main(void)
{
    float dis;
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !");
        return 1;
    }

    ultraInit();
    
    while(1){
        dis = disMeasure();
        printf("%0.2f cm\n\n",dis);
        delay(300);
    }

    return 0;
}
