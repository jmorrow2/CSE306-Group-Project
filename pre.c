#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "Flags.h"

char*** _flags;
int _num_of_fields, _num_of_records;

int main(int argc, char* argv[]){

    _flags = readFlags(argc, argv);
    if(_flags==NULL){
        return 1;
    }

  char* fileName = argv[argc -1];
  if(fileName == NULL){
	printf("%s", "ERROR, invalid file");
	return 1;
  }

  FILE* inFile = fopen(fileName, "r");

  char line[1000];
  _num_of_records = 0;

  while( fgets(line, 1000, inFile) != NULL){
    if(!_num_of_records){
      ++_num_of_records;
      continue;
    }
	//printf("%s", line);  /*Don't need the \n character in the format*/
	char* s = line;
  struct Record* element = lineToRecord(s, strlen(s));

  printRecord(element); // change this to add the struct to our record

  freeRecord(element);

/*	while(*s != '\0'){
		printf("%c", *s);
		s++;
	}*/
  ++_num_of_records;
  }

  printFlags(_flags); //FOR TESTING: max number for flag is 3 (records field value) so flags < 3 will print junk

  printf("%d\n%d\n",_num_of_records, get_num_fields());
  freeFlags(_flags);

  return 0;
}
