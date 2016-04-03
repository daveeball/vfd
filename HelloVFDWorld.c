/*
 * HelloVFDWorld.c
 *
 *  Created on: 13 Mar 2016
 *      Author: daveb
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpd/client.h>
#include <mpd/tag.h>
#include <sys/time.h>

#include "futabaVfd.h"

//static const unsigned char Smile[32] = /***/{ 0x07, 0x1E, 0x30, 0x60, 0x40, 0xCC, 0xCC, 0x80, 0x80, 0xCC,
///********************************************/0xCC, 0x40, 0x60, 0x30, 0x1E, 0x07, 0xE0, 0x78, 0x0C, 0x06,
///********************************************/0x62, 0x33, 0x33, 0x39, 0x39, 0x33, 0x33, 0x62, 0x06, 0x0C,
///********************************************/0x78, 0xE0 };
static const unsigned char SmileN[32] = /**/{ 0x07, 0xE0, 0x1E, 0x78, 0x30, 0x0C, 0x60, 0x06, 0x40, 0x62,
/********************************************/0xCC, 0x33, 0xCC, 0x33, 0x80, 0x39, 0x80, 0x39, 0xCC, 0x33,
/********************************************/0xCC, 0x33, 0x40, 0x62, 0x60, 0x06, 0x30, 0x0C, 0x1E, 0x78,
/********************************************/0x7, 0xE0 };
static const unsigned char SmileW[52] = /**/{ 0x03, 0xC0, 0x0C, 0x30, 0x10, 0x08, 0x10, 0x08, 0x20, 0x04,
/********************************************/0x20, 0x04, 0x40, 0x02, 0x40, 0x62, 0x4C, 0x32, 0x8C, 0x31,
/********************************************/0x8C, 0x11, 0x8C, 0x19, 0x80, 0x19, 0x80, 0x19, 0x8C, 0x19,
/********************************************/0x8C, 0x11, 0x8C, 0x31, 0x4C, 0x32, 0x40, 0x62, 0x40, 0x02,
/********************************************/0x20, 0x04, 0x20, 0x04, 0x10, 0x08, 0x10, 0x08, 0x0C, 0x30,
/********************************************/0x03, 0xC0 };

//static const unsigned char dude[52] = /****/{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x3E, 0x7F, 0x7F, 0xFF,
///********************************************/0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xFF, 0x7F, 0x7F, 0x3E,
///********************************************/0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x3F,
///********************************************/0x7F, 0x7F, 0xFF, 0x7F, 0x3F, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
///********************************************/0xBF, 0xBF, 0xBF, 0x3F, 0x7F, 0xFF, 0x7F, 0x7F, 0x3F, 0x3F,
///********************************************/0x1F, 0x0F };
static const unsigned char dude[52] = /****/{ 0x00, 0x0F, 0x00, 0x1F, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x7F,
/********************************************/0x1C, 0x7F, 0x3E, 0xFF, 0x7F, 0x7F, 0x7F, 0x3F, 0xFF, 0xBF,
/********************************************/0xC7, 0xBF, 0xFF, 0xBF, 0xFF, 0xBF, 0xFF, 0xBF, 0xFF, 0xBF,
/********************************************/0xC7, 0xBF, 0xFF, 0xBF, 0x7F, 0x3F, 0x7F, 0x7F, 0x3E, 0xFF,
/********************************************/0x1C, 0x7F, 0x00, 0x7F, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x1F,
/********************************************/0x00, 0x0F };

void writeDude() {
	writePixels(26, 2, (unsigned char*) dude);
}

void scrollingDudes() {
	int i;
	for (i = 1; i <= 17; i++) {
		writeDude();
		setCursor((30 * i), 0);
		delayNanoSeconds(25000000);
	}

	for (;;) {
		scroll(1);
		delayNanoSeconds(100000);
	}
}

void doScroll(unsigned char source[224], unsigned char destination[224]) {
	register unsigned int c;
	for (c = 0; c < 112; ++c) {
		destination[c] = source[c + 1];
		destination[112 + c] = source[112 + c + 1];
	}
	destination[111] = source[0];
	destination[223] = source[112];
}

void writeSineWave() {
	const long double PI = acos((long double) -1);
	unsigned char data[224];
	unsigned char scrollBuffer[224];

	long double interval = (15 * PI) / 360;
	register unsigned int i;
	for (i = 0; i <= 111; ++i) {
		int pixel = (int) floor(sin(interval * i) * 8) + 8;
		int sinValue = 1 << pixel;

		data[i] = (unsigned char) ((sinValue >> 8) & 0xFF);
		data[112 + i] = (unsigned char) (sinValue & 0xFF);
	}
	writeScreen(data);
	i = 0;
	for (;;) {
		if (i++ % 2 == 0) {
			doScroll(data, scrollBuffer);
			writeScreen(scrollBuffer);
		} else {
			doScroll(scrollBuffer, data);
			writeScreen(data);
		}
		delayNanoSeconds(100);
	}
}

// sudo apt-get install wiringpi (or install from source)
// sudo usermod -a gpio [username]
//int main(void) {
int hello_main() {

	initRPi();
	initVfd();

	writeString("This is static text");
	setCursor(0, 1);

	unsigned char *buffer = buildStringData("");
	int size = (buffer[1] * 256) + buffer[0];

	int fwd = 1;
	int location = 0;
	for (;;) {
		writePixels(112, 1, &buffer[2 + location]);
		if ((fwd == 1 && location <= (size + 112)) || (fwd == 0 && location == 0)) {
			fwd = 1;
			location++;
		} else {
			location = 0;
		}
		delayNanoSeconds(10000000);
	}
	// writePixels(16, 2, (unsigned char*) SmileN);
	// writePixels(26, 2, (unsigned char*) SmileW);
	// scrollingDudes();
	// writeSineWave();

	return 0;
}
