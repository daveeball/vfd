
void initRPi(void);
void initOuputPin(int);
void initPBusyPin(void);
void initVfd(void);

unsigned char* buildStringData(const char *);
void writeScreen(unsigned char *);
void clearScreen(void);
void writePixels(int, int, unsigned char *);
void writeString(const char *);
void setCursor(int, int);
void writeCommand(unsigned char *);
void writeByte(unsigned char);
void latchDataToVfd(void);
void delayNanoSeconds(int);
void delayMilliSeconds(int);

void scroll(int);
void selectWindow(char);
void defineWindow(char, int, int, int, int);
