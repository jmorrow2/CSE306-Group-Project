#ifndef PARSER
#define PARSER


//struct used for storing each line
typedef struct Record {

	float value;
	int ref_date;
	char *geo, *viewer, *content, *programme, *vector, *coordinate;
	struct Record *next;

} Record;


int get_num_fields();
char* getSubstring(int start, int end, char* source);
int findMatchingQuote(int start, const char* source);
void addFieldToRecord(int count, char* field, struct Record* element);
void printRecord(struct Record* element);
void addElementToList(struct Record *elem);
void freeAllRecords(struct Record* firstElem);
Record *getHead();
//void freeRecord(struct Record* element);

// void printGeo(Record *head); // for testing purposes only

Record* lineToRecord(char* line, const size_t length);


#endif
