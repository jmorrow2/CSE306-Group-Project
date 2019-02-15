#ifndef PARSER
#define PARSER




  struct Record {

	float value;
	int ref_date;
	char *geo, *viewer, *content, *programme, *vector, *coordinate;

};


int get_num_fields();
char* getSubstring(int start, int end, char* source);
int findMatchingQuote(int start, const char* source);
void addFieldToRecord(int count, char* field, struct Record* element);
void printRecord(struct Record* element);
void freeRecord(struct Record* element);

struct Record* lineToRecord(char* line, const size_t length);



#endif
