#ifndef FLAGS
#define FLAGS

char*** readFlags(int argc, char* argv[]);
void freeFlags(char*** flags);
void printFlags(char*** _flags);

#endif