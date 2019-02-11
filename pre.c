#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){

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