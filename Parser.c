#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"

int num_fields = 0;


char* getSubstring(int start, int end, char* source) {
	//get size for this substring
	int size = end - start;
	//allocate memory for substring
	char* substr = malloc((end - start +1) * sizeof(*substr));
	//start to fill it up
	int index = 0;

	while (index < size) {
		substr[index] = source[start + index];
		++index;
	}
	//null terminate the substring
	substr[index] = '\0';

	return substr;
}

int findMatchingQuote(int start, const char* source) {

	while (source[start] != '\"')
		++start;

	return start;
}



//add the correct fields to a particular record
void addFieldToRecord(int count, char* field, struct Record* element) {

	// ref_date
	if (!count) {
		//convert string to int for ref_date
		int date;
		sscanf(field, "%d", &date);

		element->ref_date = date;
	}

	//geo
	else if (count == 1)
		element->geo = field;

	//viewer
	else if (count == 2)
		element->viewer = field;

	//content
	else if (count == 3)
		element->content = field;

	//programme
	else if (count == 4)
		element->programme = field;

	//vector
	else if (count == 5)
		element->vector = field;

	//coordinates
	else if (count == 6)
		element->coordinate = field;

	//value
	else if (count == 7) {
		//convert string to float for value
		float val;
		sscanf(field, "%f", &val);

		element->value = val;
	}

}

//
struct Record* lineToRecord(char* line, const size_t length) {

	int index = 0;
	unsigned int start = 1;
	int count = 0;

	struct Record* element = malloc(sizeof(*element));

	while (start < length) {

		//is the current character is ',' get the string until then
		if (line[start] == ',') {
			char* field = getSubstring(index, start, line);
			index = start + 1;

			addFieldToRecord(count, field, element);
			++count;

			//if the current character is now '\"' get the entire string
			while (index<length && line[index] == '\"') {
				start = findMatchingQuote(index + 1, line);
				char* inner_field = getSubstring(index, start + 1, line);

				index = start + 1;
				if (index < length && line[index] == ',')
					++index;

				addFieldToRecord(count, inner_field, element);

				++count;
				start = index + 1;

				//start already advanced to next field
				continue;
			}


		}

		++start;
	}

	//handle final field
	char* field = getSubstring(index, start, line);
	addFieldToRecord(count, field, element);

	if(!num_fields)
		num_fields = count;
	//return the pointer to the struct
	return element;
}

//deallocate all the memory used for records
void freeRecord(struct Record* element) {

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
void printRecord(struct Record* element) {

	printf("%d\n%s\n%s\n%s\n%s\n%s\n%s\n%f\n\n", element->ref_date,
		element->geo, element->viewer, element->content, element->programme,
		element->vector, element->coordinate, element->value);
}

int get_num_fields(){
	return num_fields;
}
/*int main(int argc, char** argv) {

	char* line = "2004,Canada,\"Francophones, two years and older\",\"Total, all television programmes, Canadian and foreign\",Social and/or recreational instruction,v21420008,1.3.1.5,0.7";

	struct Record* element = lineToRecord(line, strlen(line));

	printRecord(element);

	freeRecord(element);

  line = "1998,Canada,\"Francophones, two years and older\",Foreign television programmes,Variety and games,v21420037,1.3.3.8,1.9";

  element = lineToRecord(line, strlen(line));

	printRecord(element);

	freeRecord(element);

	//TODO: free memory
	return 0;
}*/
