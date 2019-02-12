#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char _min_field[50], _max_field[50], _mean_field[50],
     _record_field[50], _record_value[50];
int _num_of_fields, _num_of_records; 

int main(int argc, char* argv[]){
	
int i=1;

while(i<argc-1){
    if(strcmp(argv[i], "-f")==0){
        // displayNumOfFields();
    }else
    if(strcmp(argv[i], "-r")==0){
        // displayNumOfRecords();
    }else
    if(strcmp(argv[i], "-h")==0){
        // headerNotRecord();
    }else
    if(strcmp(argv[i], "-max")==0){
        if((strcmp(argv[i+1],"Ref_Date")!=0) && (strcmp(argv[i+1],"Value")!=0)){
            printf("%s", "MUST ENTER NUMERIC FIELD");
            return 1;
        }
        strcpy(_max_field, argv[i+1]);
        i++;
    }else
    if(strcmp(argv[i], "-min")==0){
        if((strcmp(argv[i+1],"Ref_Date")!=0) && (strcmp(argv[i+1],"Value")!=0)){
            printf("%s", "MUST ENTER NUMERIC FIELD");
            return 1;
        }
        strcpy(_min_field, argv[i+1]);
        i++;
    }else
    if(strcmp(argv[i], "-mean")==0){
        if((strcmp(argv[i+1],"Ref_Date")!=0) && (strcmp(argv[i+1],"Value")!=0)){
            printf("%s", "MUST ENTER NUMERIC FIELD");
            return 1;
        }
        strcpy(_mean_field, argv[i+1]);
        i++;
    }else
    if(strcmp(argv[i], "-records")==0){
        if((strcmp(argv[i+1],"Ref_Date")!=0) && (strcmp(argv[i+1],"Value")!=0)){
            printf("%s", "MUST ENTER NUMERIC FIELD");
            return 1;
        }
        strcpy(_record_field, argv[i+1]);
        strcpy(_record_value, argv[i+2]);
        i++;
        i++;
    }
    i++;
}

  char* fileName = argv[argc -1];
  if(fileName == NULL){
	printf("%s", "ERROR, invalid file");
	return 1;
  }

  FILE* inFile = fopen(fileName, "r");

  char line[1000];
  while( fgets(line, 1000, inFile) != NULL){

	printf("%s", line);  /*Don't need the \n character in the format*/
	char* s = line;
	
	
	while(*s != '\0'){
		printf("%c", *s);
		s++;
	}
  }

  return 0;
}
