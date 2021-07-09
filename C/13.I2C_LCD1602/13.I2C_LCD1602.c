/**********************************************************************
* Filename    : 13.I2C_LCD1602.c
* Description : Control LCD Display.
* Author      : Robot
* E-mail      : support@Rexqualis.com
* website     : www.rexqualis.com
* Update      : Tim   2019/12/02
**********************************************************************/
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <string.h>

int LCDAddr = 0x27;//i2c address
int BLEN = 1;
int fd;  //the driver file

void write_word(int data){  //wrtite to the i2c data
	int temp = data;
	if ( BLEN == 1 )
		temp |= 0x08; // or get the 1 in 0000 1000
	else
		temp &= 0xF7;  // and  get the 1 in 1111 0111
	wiringPiI2CWrite(fd, temp);
}

void send_command(int comm){//send the command in twice
	int buf;
	// Send bit7-4 firstly
	buf = comm & 0xF0;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (comm & 0x0F) << 4;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

void send_data(int data){ //send the data in twice
	int buf;
	// Send bit7-4 firstly
	buf = data & 0xF0;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (data & 0x0F) << 4;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

void init(){
	send_command(0x33);	// Must initialize to 8-line mode at first
	delay(5);
	send_command(0x32);	// Then initialize to 4-line mode
	delay(5);
	send_command(0x28);	// 2 Lines & 5*7 dots
	delay(5);
	send_command(0x0C);	// Enable display without cursor
	delay(5);
	send_command(0x01);	// Clear Screen
	wiringPiI2CWrite(fd, 0x08); //end 
}

void clear(){
	send_command(0x01);	//clear Screen
}

void write(int x, int y, char data[]){
	int addr, i;
	int tmp;
	//the position of string
	if (x < 0)  x = 0;
	if (x > 15) x = 15;
	if (y < 0)  y = 0;
	if (y > 1)  y = 1;

	// Move cursor
	addr = 0x80 + 0x40 * y + x;
	send_command(addr);  //send the x y data
	
	tmp = strlen(data);
	for (i = 0; i < tmp; i++){
		send_data(data[i]);
	}//send the data 
}


void main(){
	fd = wiringPiI2CSetup(LCDAddr);  //the driver file
	init(); //init the lcd 
	write(0, 0, "Hello!");//send the hello
	write(1, 1, "From Rexqualis");//send the From Rexqualis
}
