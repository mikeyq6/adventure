#include "utils.h"

void trimLeading(char *string) {
    char *temp = (char*)malloc(strlen(string) * sizeof(char));
    int cur = 0;
    char firstCharFound = 0;

    for(int i=0; i<strlen(string); i++) {
        if(string[i] == '\0') {
            temp[cur++] = '\0';
            break;
        } else if((string[i] == ' ' || string[i] == '\t') && firstCharFound == 0) {
            continue;
        } else {
            temp[cur++] = string[i];
            firstCharFound = 1;
        }
    }

    strcpy(string, temp);
    free(temp);
}
