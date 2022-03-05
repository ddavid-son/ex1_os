#include <stdio.h>
#include <stdlib.h>
#include "string.h"


int main(){
    char sample[] = "avi 90 87   72  64       23   65";
    char* line = strtok(sample, " ");
    while(line != NULL){
        printf("%s\n", line);
        line = strtok(NULL, " ");
    }
}