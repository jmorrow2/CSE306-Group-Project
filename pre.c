#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "Flags.h"
#include <math.h>
#include <limits.h>

//structs for min max and mean for corresponding fields
typedef struct minimum{
  int ref_date;
  float value;
} minimum;

typedef struct maximum{
  int ref_date;
  float value;
} maximum;
typedef struct mean{
  int ref_date;
  float value;

  float ref_sum;
  float val_sum;

} mean;

//global variables for ease of access during calculations
int _num_of_fields, _num_of_records;
struct minimum* _min;
struct maximum* _max;
struct mean* _mean;
//prints all the lines with the corresponding date
void printAllDate(const int date){
  struct Record* trav = getHead();

  while(trav){
    if(trav->ref_date == date)
      printRecord(trav);

    trav = trav->next;
  }
}
//prints all the lines with the corresponding value
void printAllValue(const float val){
  struct Record* trav = getHead();

  while(trav){
    if(fabs(val - trav->value)<0.0001)
      printRecord(trav);

    trav = trav->next;
  }

}
//prints all the lines with the corresponding geo
void printAllGeo(char* val){
  struct Record* trav = getHead();

  while(trav){
    if(!strcmp(val,trav->geo))
      printRecord(trav);

    trav = trav->next;
  }
}
//prints all the lines with the corresponding viewers
void printAllViewer(char* val){
  struct Record* trav = getHead();

  while(trav){
    if(!strcmp(val,trav->viewer))
      printRecord(trav);

    trav = trav->next;
  }
}
//prints all the lines with the corresponding content
void printAllContent(char* val){
  struct Record* trav = getHead();

  while(trav){
    if(!strcmp(val,trav->content))
      printRecord(trav);

    trav = trav->next;
  }
}
//prints all the lines with the corresponding programme
void printAllProgram(char* val){
  struct Record* trav = getHead();

  while(trav){
    if(!strcmp(val,trav->programme))
      printRecord(trav);

    trav = trav->next;
  }
}
//prints all the lines with the corresponding vector
void printAllVector(char* val){
  struct Record* trav = getHead();

  while(trav){
    if(!strcmp(val,trav->vector))
      printRecord(trav);

    trav = trav->next;
  }
}
//prints all the lines with the corresponding coordinates
void printAllCoordinates(char* val){
  struct Record* trav = getHead();

  while(trav){
    if(!strcmp(val,trav->coordinate))
      printRecord(trav);

    trav = trav->next;
  }
}

//execute all the records using the given field
//return 0 if successful; 1 otherwise
int executeRecords(char* field, char* val){

  if(!strcmp(field, "Value")){
    float current;
    sscanf(val, "%f", &current );
    printAllValue(current);
    return 0;
  }
  else if(!strcmp(field, "Ref_Date")){
    int date;
    sscanf(val, "%d", &date);
    printAllDate(date);
    return 0;
  }
  else if (!strcmp(field, "GEO")){
    printAllGeo(val);
  }
  else if (!strcmp(field, "VIEWER")){
    printAllViewer(val);
  }
  else if (!strcmp(field, "CONTENT")){
    printAllContent(val);
  }
  else if (!strcmp(field, "PROGRAMME")){
    printAllProgram(val);
  }
  else if (!strcmp(field, "Vector")){
    printAllVector(val);
  }
  else if (!strcmp(field, "Coordinates")){
    printAllCoordinates(val);
  }

  //return 1 for any other records
  return 1;
}
//execute all the records using the given flags
//return 0 if successful; 1 otherwise
int executeFlags(char*** flags){
  for(int i=0; i<flagCount; ++i){
    //get rid oh -h
    if(!strcmp(flags[i][0],"-h")){
      continue;
    }
    //num of fields
    if(!strcmp(flags[i][0],"-f")){
      printf("%d\n",get_num_fields());
    }
    //num of records
    else if(!strcmp(flags[i][0],"-r")){
      printf("%d\n",_num_of_records);
    }
    //min
    else if(!strcmp(flags[i][0],"min")){
      if(!strcmp(flags[i][1],"Ref_Date")){
        printf("%d\n",_min->ref_date );
      }
      else if(!strcmp(flags[i][1], "Value")){
        printf("%.1f\n",_min->value );
      }
      else{
        return 1;
      }
    }
    //max
    else if(!strcmp(flags[i][0],"max")){
      if(!strcmp(flags[i][1],"Ref_Date")){
        printf("%d\n",_max->ref_date );
      }
      else if(!strcmp(flags[i][1], "Value")){
        printf("%.1f\n",_max->value );
      }
      else{
        return 1;
      }

    }
    //mean
    else if(!strcmp(flags[i][0],"mean")){
      if(!strcmp(flags[i][1],"Ref_Date")){
        printf("%d\n",_mean->ref_date );
      }
      else if(!strcmp(flags[i][1], "Value")){
        printf("%.2f\n",_mean->value );
      }
      else{
        return 1;
      }
    }
    //records
    else if(!strcmp(flags[i][0],"records")){
      int result = executeRecords(flags[i][1], flags[i][2]);
      if(result) return result;
    }

      //else return for garbage field
      else{
        return 1;
      }

 }
 //return 0 if successfully executed
  return 0;
}

int main(int argc, char* argv[]){
//store the flags into a 2D array of strings

    if(argc==1){
      printf("%s\n","No flags provided!" );
        return 1;
    }
    char*** _flags = readFlags(argc, argv);
    if(!_flags){
      printf("%s\n","Please provide valid flags!" );
        return 1;
    }
//get filename
  char* fileName = argv[argc -1];
  if(fileName == NULL){
	printf("%s", "ERROR, invalid file\n");
  freeFlags(_flags);
	return 1;
  }

  FILE* inFile = fopen(fileName, "r");
//if file does not open, return 1
  if(inFile == NULL){
  printf("%s", "ERROR, invalid file\n");
  freeFlags(_flags);
  return 1;
  }
//
  char line[1000];
  _num_of_records = 0;

  //setup structs for calculations
  _min = malloc(sizeof(*_min));
  _min->value = INT_MAX; _min->ref_date = INT_MAX;
  _max = malloc(sizeof(*_max));
  _max->value = INT_MIN; _max->ref_date = INT_MIN;
  _mean = malloc(sizeof(*_mean));
  _mean->val_sum = 0.0; _mean->ref_sum = 0;

//read file and build linked list of records
int count = 0;
  while( fgets(line, 1000, inFile) != NULL){
    //ignore first line if -h flag given
    if((contains_head) && (!count)){
      ++count;
      continue;
    }
	//printf("%s", line);  /*Don't need the \n character in the format*/
	char* s = line;
  struct Record* element = lineToRecord(s, strlen(s));

  //printRecord(element); // change this to add the struct to our record

  addElementToList(element);  // still working on function

  //keep a running tally of min
  _min->ref_date = element->ref_date<_min->ref_date?element->ref_date:_min->ref_date;
  _min->value = element->value<_min->value?element->value:_min->value;
  //keep a running tally of max
  _max->ref_date = element->ref_date>_max->ref_date?element->ref_date:_max->ref_date;
  _max->value = element->value>_max->value?element->value:_max->value;
  //keep a running tally of the sum
  _mean->ref_sum += element->ref_date;
  _mean->val_sum += element->value;

  ++_num_of_records;
  }
  //compute mean after computing total sum
  _mean->ref_date = (_mean->ref_sum)/(float)_num_of_records;
  _mean->value = (_mean->val_sum)/(float)_num_of_records;


  //execute all the flags after reading the file has been completed
  int exit = executeFlags(_flags);

  //free 2D array of strings used for flafs
  freeFlags(_flags);
  //free structs for calculations
  free(_min);
  free(_max);
  free(_mean);

  //free all the records
  freeAllRecords(getHead());

  //return operation success code
  return exit;
}
