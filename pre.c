#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"

char*** _flags;
int _num_of_fields, _num_of_records;

int main(int argc, char* argv[]){

//Allocate 3d array _flags
_flags = (char***) malloc(sizeof(char***) * 100);
for (int i = 0; i < 10; i++) {
    _flags[i] = (char **) malloc(sizeof(char*)*100);
    for (int k = 0; k < 10; k++) {
        _flags[i][k] = (char *) malloc(sizeof(char)*3);
    }
}

//Read in flags and store in _flags
int i=1;
int flagCount=0;
while(i<argc-1){
    if(strcmp(argv[i], "-f")==0){
        strcpy(_flags[flagCount][0], "-f");
        flagCount++;
    }else
    if(strcmp(argv[i], "-r")==0){
        strcpy(_flags[flagCount][0], "-r");
        flagCount++;
    }else
    if(strcmp(argv[i], "-h")==0){
        strcpy(_flags[flagCount][0], "-h");
        flagCount++;
    }else
    if(strcmp(argv[i], "-max")==0){
        if((strcmp(argv[i+1],"Ref_Date")!=0) && (strcmp(argv[i+1],"Value")!=0)
            && (strcmp(argv[i+1], "0")!=0) && (strcmp(argv[i+1], "7")!=0)) {
            printf("%s", "MUST ENTER NUMERIC FIELD");
            return 1;
        }
        if((strcmp(argv[i+1], "Ref_Date")==0) || (strcmp(argv[i+1], "0")==0)){
            strcpy(_flags[flagCount][0], "max");
            strcpy(_flags[flagCount][1], "Ref_Date");
            flagCount++;
        } 
        if((strcmp(argv[i+1], "Value")==0) || (strcmp(argv[i+1], "7")==0)){
            strcpy(_flags[flagCount][0], "max");
            strcpy(_flags[flagCount][1], "Value");
            flagCount++;
        }
        i++;
    }else
    if(strcmp(argv[i], "-min")==0){
        if((strcmp(argv[i+1],"Ref_Date")!=0) && (strcmp(argv[i+1],"Value")!=0)
        && (strcmp(argv[i+1], "0")!=0) && (strcmp(argv[i+1], "7")!=0)){
            printf("%s", "MUST ENTER NUMERIC FIELD");
            return 1;
        }
        if((strcmp(argv[i+1], "Ref_Date")==0) || (strcmp(argv[i+1], "0")==0)){
            strcpy(_flags[flagCount][0], "min");
            strcpy(_flags[flagCount][1], "Ref_Date");
            flagCount++;
        } 
        if((strcmp(argv[i+1], "Value")==0) || (strcmp(argv[i+1], "7")==0)){
            strcpy(_flags[flagCount][0], "min");
            strcpy(_flags[flagCount][1], "Value");
            flagCount++;
        }
        i++;
    }else
    if(strcmp(argv[i], "-mean")==0){
        if((strcmp(argv[i+1],"Ref_Date")!=0) && (strcmp(argv[i+1],"Value")!=0)
        && (strcmp(argv[i+1], "0")!=0) && (strcmp(argv[i+1], "7")!=0)){
            printf("%s", "MUST ENTER NUMERIC FIELD");
            return 1;
        }
        if((strcmp(argv[i+1], "Ref_Date")==0) || (strcmp(argv[i+1], "0")==0)){
            strcpy(_flags[flagCount][0], "mean");
            strcpy(_flags[flagCount][1], "Ref_Date");
            flagCount++;
        } 
        if((strcmp(argv[i+1], "Value")==0) || (strcmp(argv[i+1], "7")==0)){
            strcpy(_flags[flagCount][0], "mean");
            strcpy(_flags[flagCount][1], "Value");
            flagCount++;
        }
        i++;
    }else
    if(strcmp(argv[i], "-records")==0){
        strcpy(_flags[flagCount][0], "records");
        strcpy(_flags[flagCount][1], argv[i+1]);
        strcpy(_flags[flagCount][2], argv[i+2]);
        flagCount++;
        i++;
        i++;
    }
    i++;
}
	
//FOR TESTING: prints _flags
// for (int i = 0; i < flagCount; i++) {
//     printf("Flag %d: ", i);
	//max number for flag is 3 (records field value) so flags < 3 may print junk
//     for (int j = 0; j < 3; j++) {
//             printf("%s ", _flags[i][j]);
//         }
//     printf("\n");
// }


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

//Deallocate _flags
for(int i = 0; i<100; i++){
    for(int j =0; j <100; j++){
            free(_flags[i][j]);
    }
    free(_flags[i]);
}
free(_flags);


/*	while(*s != '\0'){
		printf("%c", *s);
		s++;
	}*/
  ++_num_of_records;
  }

 printf("%d\n%d\n",_num_of_records, get_num_fields());
  return 0;
}
