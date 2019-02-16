#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flags.h"

int flagCount=0;

char*** readFlags(int argc, char* argv[]){    
    char *** _flags = (char***) malloc(sizeof(char***)*10);
    for (int i = 0; i < 10; i++) {
        _flags[i] = (char **) malloc(sizeof(char*)*10);
        for (int k = 0; k < 10; k++) {
            _flags[i][k] = (char *) malloc(sizeof(char)*10);
        }
    }

    int i=1;
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
                return NULL;
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
                return NULL;
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
                return NULL;
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
        }else{
            printf("%s", "INVALID FLAG");
            return NULL;
        }
        i++;
    }
    return _flags;
}


void freeFlags(char*** _flags){
    for(int i = 0; i<10; i++){
        for(int j =0; j <10; j++){
                free(_flags[i][j]);
        }
        free(_flags[i]);
    }
    free(_flags);
}


void printFlags(char*** _flags){
    for (int i = 0; i < flagCount; i++) {
        printf("Flag %d: ", i);
        // max number for flag is 3 (records field value) so flags < 3 may print junk
        for (int j = 0; j < 3; j++) {
                printf("%s ", _flags[i][j]);
            }
        printf("\n");
    }
}