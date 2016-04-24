#define _POSIX_C_SOURCE	199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bcm2835.h"

#include "font5x7.h"
#include "futabaVfd.h"

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
static const unsigned char CMD_Home[2] = /*************/{ 1, 0x0B };
static const unsigned char CMD_DisplayClear[2] = /*****/{ 1, 0x0C };
static const unsigned char CMD_InitialiseDisplay[3] = { 2, 0x1B, 0x40 };
static const unsigned char CMD_HorizontalScrollMode[3] = { 2, 0x1F, 0x03 };
static const unsigned char CMD_BrightnessLevel[4] = /**/{ 3, 0x1F, 0x58, 0x00 }; // 0x04=[50%], 0x08=[100%]
static const unsigned char CMD_Proportional[6] = /*****/{ 5, 0x1F, 0x28, 0x67, 0x03, 0x02 };
static const unsigned char CMD_WholeScreenMode[6] = /**/{ 5, 0x1F, 0x28, 0x77, 0x10, 0x01 };
//static const unsigned char CMD_LineFeed[2] = /*********/{ 1, 0x0A };
//static const unsigned char CMD_OverwriteMode[3] = /****/{ 2, 0x1F, 0x01 };
//static const unsigned char CMD_ReverseCancel[4] = /****/{ 3, 0x1F, 0x72, 0x00 };
//static const unsigned char CMD_ReverseApply[4] = /*****/{ 3, 0x1F, 0x72, 0x01 };
//static const unsigned char CMD_MagnifyWide[7] = /******/{ 6, 0x1F, 0x28, 0x67, 0x40, 0x03, 0x01 };
//static const unsigned char CMD_MagnifyNormal[7] = /****/{ 6, 0x1F, 0x28, 0x67, 0x40, 0x01, 0x01 };
//static const unsigned char CMD_MagnifyHuge[7] = /******/{ 6, 0x1F, 0x28, 0x67, 0x40, 0x02, 0x02 };
//static const unsigned char CMD_Blink_fast[9] = /*******/{ 8, 0x1F, 0x28, 0x61, 0x11, 0x02, 0x02, 0x01, 0x00 };
//static const unsigned char CMD_Blink_slow[9] = /*******/{ 8, 0x1F, 0x28, 0x61, 0x11, 0x02, 0x20, 0x10, 0x00 };

/////////////////////////////////////////////////////////
// Private
void latchDataToVfd(void);
void writeByte(unsigned char);
void writeCommand(unsigned char *);
/////////////////////////////////////////////////////////

unsigned char* buildStringData(const char *text) {
	printf("Rendering %s\n", text);
	register unsigned int length = 0;
	while (text[length] != 0) {
		length++;
	}
	unsigned char *pixels = malloc(length * 6 * sizeof(unsigned char));

	register unsigned int i = 0;
	register unsigned int c = 0;
	while (text[c] != 0) {
		if (text[c] == 32) {
			pixels[i++] = 0x00; // three pixel space.
			pixels[i++] = 0x00;
			pixels[i++] = 0x00;
		} else if (text[c] < 255) {
			int position = ((text[c] - 32) * 5);
			for (unsigned char d = 0; d < 5; d++) {
				unsigned char byte = Font5x7[position + d];
				if (byte > 0) {
					pixels[i++] = byte;
				}
			}
			pixels[i++] = 0x00; // one pixel gap.
		}
		c++;
	}

	if (i > (255 * 255)) {
		fprintf(stderr, "Error - too many pixels to render...\n");
		i = 255 * 255;
	}

	unsigned char *data = malloc((2 + i + 224) * sizeof(unsigned char));
	data[0] = (i & 0xFF); //#no of pixels
	data[1] = ((i >> 8) & 0xFF); //#no of pixels

	// TODO more efficient copy?
	for (int p = 0; p <= i; p++) {
		data[p + 2 + 112] = pixels[p];
	}
	memset(&data[2], 0, 112 * sizeof(unsigned char));
	memset(&data[2 + i + 112], 0, 112 * sizeof(unsigned char));

	return data;
}

/////////////////////////////////////////////////////////

void scroll(int pixels) {
	if (pixels > 511) {
		fprintf(stderr, "pixels to scroll must be less than 512\n");
		return;
	}
	int memoryLocations = pixels * 2;
	unsigned char cmd[10] = { 9, 0x1F, 0x28, 0x61, 0x10, (memoryLocations & 0xFF), ((memoryLocations >> 8) & 0xFF),
			0x01, 0x00, 0x00 };
	writeCommand(cmd);
}

void setCursor(int x, int y) {
	if (y > 1) {
		fprintf(stderr, "Cursor Y-position must be 0 or 1\n");
		return;
	}
	if (x > 511) {
		fprintf(stderr, "Cursor X-position must be less than 512\n");
		return;
	}

	unsigned char cmd[7] = { 6, 0x1F, 0x24, (x & 0xFF), ((x >> 8) & 0xFF), (y & 0xFF), ((y >> 8) & 0xFF) };
	writeCommand(cmd);
}

void writePixels(int width, int height, unsigned char* bytes) {
	if (width < 1 || width > 511) {
		fprintf(stderr, "Graphics width must be between 1 and 511\n");
		return;
	}
	if (height < 1 || height > 2) {
		fprintf(stderr, "Graphics height must be 1 or 2\n");
		return;
	}

	unsigned char cmd[10] = { 9, 0x1F, 0x28, 0x66, 0x11, (width & 0xFF), ((width >> 8) & 0xFF), (height & 0xFF),
			((height >> 8) & 0xFF), 0x01 };
	writeCommand(cmd);
	register unsigned char x;
	register unsigned char y;
	for (x = 0; x < width; ++x) {
		for (y = 0; y < height; ++y) {
			writeByte(bytes[(x * height) + y]);
			// printf("Data at %d,%d = 0x%02x\n", x, y, bytes[(x * height) + y]);
		}
	}
}

void clearScreen() {
	writeCommand((unsigned char*) CMD_DisplayClear);
	writeCommand((unsigned char*) CMD_Home);
}

/////////////////////////////////////////////////////////

void initOuputPin(int pin) {
	bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
}

void initPBusyPin() {
	bcm2835_gpio_fsel(PBUSY, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fen(PBUSY);
	// Clear the flag.
	bcm2835_gpio_set_eds(PBUSY);
}

void initRPi() {
	if (!bcm2835_init()) {
		fprintf(stderr, "Failed to initialise GPIO access.\n");
		return;
	}
	initOuputPin(WR);
	initPBusyPin();
	bcm2835_gpio_write(WR, LOW);
	register unsigned char i;
	for (i = 0; i < 8; ++i) {
		initOuputPin(dataPins[i]);
	}
}

void initVfd(void) {
	writeCommand((unsigned char*) CMD_InitialiseDisplay);
	writeCommand((unsigned char*) CMD_HorizontalScrollMode);
	writeCommand((unsigned char*) CMD_BrightnessLevel);

	writeCommand((unsigned char*) CMD_Proportional);
	writeCommand((unsigned char*) CMD_WholeScreenMode);
	writeCommand((unsigned char*) CMD_DisplayClear);
	writeCommand((unsigned char*) CMD_Home);
}

void shutdownVfd() {
	printf("Shutdown...");
	bcm2835_close();
}

void writeString(const char *data) {
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
		bcm2835_gpio_write(dataPins[i], (myData & 1));
		myData >>= 1;
	}
	latchDataToVfd();
}

void waitForPBusy() {
	do {
		delayNanoSeconds(1000);
	} while (!bcm2835_gpio_eds(PBUSY));
	// Clear the flag.
	bcm2835_gpio_set_eds(PBUSY);
}

void latchDataToVfd(void) {
	bcm2835_gpio_write(WR, HIGH); // Trigger module to read
	waitForPBusy();
	bcm2835_gpio_write(WR, LOW);
}

void delayNanoSeconds(int nanoseconds) {
	// This won't actually be reliable for small number of nanoseconds. It allows the OS to decide when I should run again, with a wait of AT LEAST the requested time.
	struct timespec tim;
	struct timespec tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = nanoseconds;
	nanosleep(&tim, &tim2);
}

void delayMilliSeconds(int milliseconds) {
	// This is also unreliable.
	bcm2835_delay(milliseconds);
}
