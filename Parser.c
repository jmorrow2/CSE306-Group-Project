#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record{

double value;
int ref_date;
char *geo, *viewer, *content, *programme, *vector, *coordinate;

};

char* getSubstring(int start, int end, char* source){
  //get size for this substring
  int size = end - start;
  //allocate memory for substring
  char* substr = malloc((end-start)*sizeof(*substr));
  //start to fill it up
  int index = 0;

  while(index<size){
    substr[index] = source[start+index];
    ++index;
  }
  //null terminate the substring
  substr[index] = '\0';

  return substr;
}

int findMatchingQuote(int start, const char* source){

  while(source[start]!='\"')
      ++start;

  return start;
}



//add the correct fields to a particular record
void addFieldToRecord(int count, char* field, struct Record* element){

  // ref_date
  if (!count){
      //convert string to int for ref_date
      int date;
      sscanf(field, "%d", &date);

      element->ref_date = date;
  }

  //geo
  else if(count == 1)
    element->geo = field;

  //viewer
  else if(count == 2)
    element->viewer = field;

  //content
  else if(count==3)
    element->content = field;

  //programme
  else if(count==4)
    element->programme = field;

  //vector
  else if(count==5)
    element->vector = field;

  //coordinates
  else if(count == 6)
    element->coordinate = field;

  //value
  else if(count == 7){
    //convert string to double for value
    double val;
    sscanf(field, "%lf", &val);

    element->value = val;
  }

}

//
struct Record* lineToRecord(char* line, const size_t length){

  int index = 0;
  int start = 1;
  int count = 0;

  struct Record* element = malloc(sizeof(*element));

  while(start<length){

      if(line[start]==','){
          char* field = getSubstring(index, start, line);
          index = start + 1;

          addFieldToRecord(count, field, element);

          ++start;
          ++count;
      }

      else if(line[start]=='\"'){
        start = findMatchingQuote(start+1, line);
        char* field = getSubstring(index, start, line);
        
        index = start + 1;

        addFieldToRecord(count, field, element);

        ++start;
        ++count;
      }

      ++start;
  }

  return element;
}

//deallocate all the memory used for records
void freeRecord(struct Record* element){

  //free all the string fields first

  free(element->geo);
  free(element->viewer);
  free(element->content);
  free(element->programme);
  free(element->vector);
  free(element->coordinate);


  //free the record itself
  free(element);

}

//temp function to print all the fields of a records
void printRecord(struct Record* element){

  printf("%d\n,%s\n,%s\n,%s\n,%s\n,%s\n,%s\n,%lf\n", element->ref_date,
          element->geo, element->viewer, element->content, element->programme,
          element->vector, element->coordinate, element->value);
}

int main(int argc, char** argv){

  char* line = "2004,Canada,\"Total, all persons two years and older\",\"Total, all television programmes, Canadian and foreign\",News and public affairs,v21419927,1.1.1.2,24.4";

  struct Record* element = lineToRecord(line, strlen(line));

  printRecord(element);

  freeRecord(element);


  //printf("%s\n%ld\n%c\n", line, strlen(line), line[155]);

  //TODO: free memory
  return EXIT_SUCCESS;
}
