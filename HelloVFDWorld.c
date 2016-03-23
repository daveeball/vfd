/*
 * HelloVFDWorld.c
 *
 *  Created on: 13 Mar 2016
 *      Author: daveb
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "wiringPi.h"

#define	WR	  23 // header pin 16
#define	PBUSY 24 // header pin 18

#define D0	 4 // header pin  7
#define D1	17 // header pin 11
#define D2	27 // header pin 13
#define D3	22 // header pin 15
#define D4	 5 // header pin 29
#define D5	 6 // header pin 31
#define D6	13 // header pin 33
#define D7	26 // header pin 37

static const int dataPins[8] = { D0, D1, D2, D3, D4, D5, D6, D7 };

//////////////////////////
// Commands - taken from datasheet.
// Fist value is the number of instructions in a command (including data)
static const unsigned char CMD_LineFeed[2] = /*********/{ 1, 0x0A };
static const unsigned char CMD_Home[2] = /*************/{ 1, 0x0B };
static const unsigned char CMD_DisplayClear[2] = /*****/{ 1, 0x0C };
static const unsigned char CMD_InitialiseDisplay[3] = { 2, 0x1B, 0x40 };
static const unsigned char CMD_OverwriteMode[3] = /****/{ 2, 0x1F, 0x01 };
static const unsigned char CMD_BrightnessLevel[4] = /**/{ 3, 0x1F, 0x58, 0x08 }; // 0x04=[50%], 0x08=[100%]
static const unsigned char CMD_Proportional[6] = /*****/{ 5, 0x1F, 0x28, 0x67, 0x03, 0x02 };
static const unsigned char CMD_MagnifyWide[7] = /******/{ 6, 0x1F, 0x28, 0x67, 0x40, 0x03, 0x01 };
static const unsigned char CMD_MagnifyNormal[7] = /****/{ 6, 0x1F, 0x28, 0x67, 0x40, 0x01, 0x01 };
static const unsigned char CMD_MagnifyHuge[7] = /******/{ 6, 0x1F, 0x28, 0x67, 0x40, 0x02, 0x02 };
static const unsigned char CMD_WholeScreenMode[6] = /**/{ 5, 0x1F, 0x28, 0x77, 0x10, 0x1 };
static const unsigned char CMD_Blink[9] = /************/{ 8, 0x1F, 0x28, 0x61, 0x11, 0x01, 0x40, 0x40, 0x00 };
static const unsigned char CMD_Scroll[10] = /**********/{ 9, 0x1F, 0x28, 0x61, 0x10, 0x02, 0x00, 0x01, 0x00, 0x00 };

void initRPi(void);
void initOuputPin(int);
void initPBusyPin(void);
void initVfd(void);
void writeString(char *);
void writeCommand(unsigned char *);
void writeByte(unsigned char);
void latchDataToVfd(void);
void delayNanoSeconds(int);

// sudo apt-get install wiringpi (or install from source)
// sudo usermod -a gpio [username]
int main(void) {

	wiringPiSetupSys();
	initRPi();
	initVfd();

	writeCommand((unsigned char*) CMD_MagnifyHuge);
	writeString("Brendan!");
	delayMicroseconds(5000000); // 5 seconds

	writeCommand((unsigned char*) CMD_DisplayClear);
	writeCommand((unsigned char*) CMD_Home);
	writeCommand((unsigned char*) CMD_MagnifyWide);
	writeString("Top line");
	writeCommand((unsigned char*) CMD_Home);
	writeCommand((unsigned char*) CMD_LineFeed);
	writeCommand((unsigned char*) CMD_MagnifyNormal);
	writeString("Welcome to Tomorrow. This is far too long to display! Scrolling scrolling scrolling...");
	delayMicroseconds(2500000); // 25 seconds
	for (;;) {
		writeCommand((unsigned char*) CMD_Scroll);
		delayMicroseconds(10000);
	}
	return 0;
}

void initRPi() {
	initOuputPin(WR);
	initPBusyPin();
	digitalWrite(WR, LOW);
	register unsigned char i;
	for (i = 0; i < 8; ++i) {
		initOuputPin(dataPins[i]);
	}
}

void initOuputPin(int pin) {
	char command[50];
	sprintf(command, "/usr/local/bin/gpio export %d out", pin);
	system(command);
}

void initPBusyPin() {
	char command[50];
	sprintf(command, "/usr/local/bin/gpio edge %d falling", PBUSY);
	system(command);
}

void initVfd(void) {
	writeCommand((unsigned char*) CMD_InitialiseDisplay);
	writeCommand((unsigned char*) CMD_OverwriteMode);
	writeCommand((unsigned char*) CMD_BrightnessLevel);

	writeCommand((unsigned char*) CMD_Proportional);
	writeCommand((unsigned char*) CMD_WholeScreenMode);
	writeCommand((unsigned char*) CMD_DisplayClear);
	writeCommand((unsigned char*) CMD_Home);
}

void writeString(char *data) {
	register unsigned int i = 0;
	while (data[i] != 0) {
		writeByte(data[i]);
		i++;
	}
}

void writeCommand(unsigned char *data) {
	int cmdLength = data[0];

	register unsigned char i;
	for (i = 1; i <= cmdLength; ++i) {
		writeByte(data[i]);
	}
}

void writeByte(unsigned char data) {
	register unsigned char i;
	register unsigned char myData = data;

	for (i = 0; i < 8; ++i) {
		digitalWrite(dataPins[i], (myData & 1));
		myData >>= 1;
	}
	latchDataToVfd();
}

void latchDataToVfd(void) {
	delayNanoSeconds(101); // min 100ns since last write, 50ns since data lines settled.
	digitalWrite(WR, HIGH); // Trigger module to read
	waitForInterrupt(PBUSY, -1);
	delayNanoSeconds(101);
	digitalWrite(WR, LOW);
}

void delayNanoSeconds(int nanoseconds) {
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = nanoseconds;
	nanosleep(&tim, &tim2);
}
