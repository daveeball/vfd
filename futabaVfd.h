
void initRPi(void);
void initOuputPin(int);
void initPBusyPin(void);
void initVfd(void);

void writeScreen(unsigned char *);
void writePixels(int, int, unsigned char *);
void writeString(char *);
void setCursor(int, int);
void writeCommand(unsigned char *);
void writeByte(unsigned char);
void latchDataToVfd(void);
void delayNanoSeconds(int);
void delayMilliSeconds(int);

void scroll(int);
void selectWindow(char);
void defineWindow(char, int, int, int, int);
