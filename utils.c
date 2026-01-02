#include "utils.h"
#include <stdio.h>
void trimLeading(char *string, int replaceLB) {
    char *temp = (char*)malloc(strlen(string) * sizeof(char));
    int cur = 0;
    char firstCharFound = 0;

    for(int i=0; i<strlen(string); i++) {
        if(string[i] == '\0') {
            temp[cur++] = '\0';
            break;
        } else if(string[i] == '\r' || string[i] == '\n') {
            if(replaceLB) {
                temp[cur++] = ' ';
            }
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

int trimEntryNumber(char *string) {
    char *temp = (char*)malloc(strlen(string) * sizeof(char));
    char *strNum = (char*)malloc(5 * sizeof(char));
    int numEnd = 0;
    int cur = 0;
    int num = 0;

    for(int i=0; i<strlen(string); i++) {
        if((string[i] == '-' || (string[i] >= '0' && string[i] <= '9')) && numEnd == 0) {
            strNum[i] = string[i];
        } else {
            strNum[4] = '\0';
            numEnd = 1;
            temp[cur++] = string[i];
        }
    }
    num = atoi(strNum);

    // printf("strNum='%s', num=%d\n", strNum, num);

    strcpy(string, temp);
    free(temp);
    free(strNum);

    return num;
}
