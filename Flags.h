#ifndef FLAGS
#define FLAGS

char*** readFlags(int argc, char* argv[]);
void freeFlags(char*** flags);
void printFlags(char*** _flags);
int flagCount;
//check used to record the -h being used 
int contains_head;

#endif
