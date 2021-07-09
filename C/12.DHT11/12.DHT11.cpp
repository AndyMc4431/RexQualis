/**********************************************************************
* Filename    : 12.DHT11.cpp
* Description : DHT Temperature & Humidity Sensor library for Raspberry
* Author      : Robot
* E-mail      : support@rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim    2019/12/02
**********************************************************************/

#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include "DHT11.hpp"

#define DHT11_Pin  0    
//Function: Read DHT sensor, store the original data in bits[]
// return values:DHTLIB_OK   DHTLIB_ERROR_CHECKSUM  DHTLIB_ERROR_TIMEOUT
int DHT::readSensor(int pin,int wakeupDelay){  
	//series data read
	int mask = 0x80; //1000 0000
	int idx = 0;
	int i ;
	int32_t t;
					//init the data
	for (i=0;i<5;i++){
		bits[i] = 0;
	}
	
	//this pin can input or ouput
	pinMode(pin,OUTPUT);
	digitalWrite(pin,LOW);   //send the begin data 
	delay(wakeupDelay);
	digitalWrite(pin,HIGH);
	delayMicroseconds(40);   //0.04ms to delay
	pinMode(pin,INPUT);
	
	int32_t loopCnt = DHTLIB_TIMEOUT;
	t = micros();    //timer to commucate
	while(digitalRead(pin)==LOW){  //low to respond
		if((micros() - t) > loopCnt){
			return DHTLIB_ERROR_TIMEOUT;   //time out
		}
	}
	loopCnt = DHTLIB_TIMEOUT;
	t = micros();
	while(digitalRead(pin)==HIGH){ //high to send
		if((micros() - t) > loopCnt){
			return DHTLIB_ERROR_TIMEOUT;  //time  out
		}
	}
	for (i = 0; i<40;i++){
		loopCnt = DHTLIB_TIMEOUT;
		t = micros();
		while(digitalRead(pin)==LOW){ //low to respond
			if((micros() - t) > loopCnt)
				return DHTLIB_ERROR_TIMEOUT;  //time out
		}
		t = micros();
		loopCnt = DHTLIB_TIMEOUT;
		while(digitalRead(pin)==HIGH){ ///high to send
			if((micros() - t) > loopCnt){
				return DHTLIB_ERROR_TIMEOUT; //time out
			}
		}
		if((micros() - t ) > 60){
			bits[idx] |= mask;  //get the 1 in 1000 000 
		}
		mask >>= 1;  // right push 
		if(mask == 0){
			mask = 0x80;
			idx++;
		}
	}
	pinMode(pin,OUTPUT);
	digitalWrite(pin,HIGH);//hall
	//printf("bits:\t%d,\t%d,\t%d,\t%d,\t%d\n",bits[0],bits[1],bits[2],bits[3],bits[4]);
	return DHTLIB_OK;
}
//Function：Read DHT sensor, analyze the data of temperature and humidity
//return：DHTLIB_OK   DHTLIB_ERROR_CHECKSUM  DHTLIB_ERROR_TIMEOUT
int DHT::readDHT11(int pin){
	int rv ; 
	uint8_t sum;
	rv = readSensor(pin,DHTLIB_DHT11_WAKEUP); //series read
	if(rv != DHTLIB_OK){
		humidity = DHTLIB_INVALID_VALUE;
		temperature = DHTLIB_INVALID_VALUE;
		return rv;
	}
									//calculate
	humidity = bits[0];
	temperature = bits[2] + bits[3] * 0.1;
	sum = bits[0] + bits[1] + bits[2] + bits[3];
	if(bits[4] != sum)
		return DHTLIB_ERROR_CHECKSUM;
	return DHTLIB_OK;
}

int main(){
    DHT dht;        //create a DHT class object
    int check;//check:read the return value of sensor
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screen
        printf("setup wiringPi failed !");
        return 1; 
    }
    while(1){
        check = dht.readDHT11(DHT11_Pin); //read DHT11 and get a return value. Then determine whether data read is normal according to the return value.
        switch(check){
            case DHTLIB_OK:     //if the return value is DHTLIB_OK, the data is normal.
                printf("Humidity : %.2f, \t Temperature : %.2f \n",dht.humidity,dht.temperature); 
                break;
            case DHTLIB_ERROR_CHECKSUM:     //data check has errors
                printf("Humidity : %.2f, \t Temperature : %.2f\t (this value may be incorrect)\n",dht.humidity,dht.temperature);
                break;
            // case DHTLIB_ERROR_TIMEOUT:      //reading DHT times out
            //     printf("Timeout! \n");
            //     break;
            // case DHTLIB_INVALID_VALUE:      //other errors
            //     printf("Unknow problem! \n");
            //     break;
        }
        delay(2000);
    }   
    return 1;
}


