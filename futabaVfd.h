
void initRPi(void);
void initVfd(void);
void shutdownVfd(void);

unsigned char* buildStringData(const char *);
void clearScreen(void);
void writePixels(int, int, unsigned char *);
void writeString(const char *);
void setCursor(int, int);
void delayNanoSeconds(int);
void delayMilliSeconds(int);

void scroll(int);
