#include "adventure.h"
#include "utils.h"

int main(int argc, char **argv) {
    init();
    run();
    end();
    return 0;
}

void init(void) {
    currentLocation = 1;
    locations = (Location *)malloc(sizeof(Location) * NUM_LOCATIONS);
    for(int i=0; i<NUM_LOCATIONS; i++) {
        locations[i].long_description = (char *)malloc(sizeof(char) * 500);
        locations[i].short_description = (char *)malloc(sizeof(char) * 100);
    }
    words = (Word *)malloc(sizeof(Word) * NUM_WORDS);
    for(int i=0; i<NUM_WORDS; i++) {
        words[i].text = (char *)malloc(sizeof(char) * 5);
    }
    travelRules = (TravelRule *)malloc(sizeof(TravelRule) * NUM_TRAVEL_RULES);
    randoms = (Random*)malloc(sizeof(Random*) * NUM_RANDOMS);
    for(int i=0; i<NUM_RANDOMS; i++) {
        randoms[i].description = (char*)malloc(sizeof(char) * 1500);
    }
    objectDescriptions = (ObjectText*)malloc(sizeof(ObjectText*) * NUM_OBJECT_DESC);
    for(int i=0; i<NUM_OBJECT_DESC; i++) {
        objectDescriptions[i].text = (char*)malloc(sizeof(char) * 200);
    }
    
    setup = 1;
    keys = 1;
    lamp = 2;
    grate = 3;
    rod = 5;
    bird = 7;
    nugget = 10;
    snake = 11;
    food = 19;
    water = 20;
    axe = 21;

    for(int i=0; i<300; i++) {
        stext[i] = 0;
        if(i < 200) btext[i] = 0;
        if(i < 100) rtext[i] = 0;
        ltext[i] = 0;
    }

    readData();
}

void end(void) {    
    for(int i=0; i<NUM_LOCATIONS; i++) {
        free(locations[i].long_description);
        free(locations[i].short_description);
    }
    free(locations);
    for(int i=0; i<NUM_WORDS; i++) {
        free(words[i].text);
    }
    free(words);
    free(travelRules);
    for(int i=0; i<NUM_RANDOMS; i++) {
        free(randoms[i].description);
    }
    free(randoms);
    for(int i=0; i<NUM_OBJECT_DESC; i++) {
        free(objectDescriptions[i].text);
    }
    free(objectDescriptions);
    free(currentMove);
}

void readData(void) {
    int ikind = 0;
    FILE *fp;
    fp = fopen("data.txt", "r");
    char *sc = (char*)malloc(sizeof(char) * 3);

    int section = 0;
    while(section >= 0 && ikind++ < 10) {
        fgets(sc, 3, fp);
        section = atoi(sc);
        #ifdef DEBUG_DATA_PARSING
        printf("Section: %d\n", section);
        #endif
        switch(section) {
            case 1:
                loadLongLocationDescriptions(fp);
                break;
            case 2:
                loadShortLocationDescriptions(fp);
                break;
            case 3:
                loadTravelData(fp);
                break;
            case 4:
                loadWords(fp);
                break;
            case 5:
                loadObjectDescriptions(fp);
                break;
            case 6:
                loadSpecials(fp);
                break;
            case 0:
                section = -1;
                break;
        }
        
    }
}

void loadLongLocationDescriptions(FILE *fp) {
    char *line = (char*)malloc(sizeof(char) * 100);
    int lineNumber = 0;

    do {
        fgets(line, 100, fp);
        lineNumber = trimEntryNumber(line);
        if(lineNumber == -1) {
            break;
        }

        trimLeading(line, 1);

        if(strlen(locations[lineNumber].long_description) == 0) {
            strcpy(locations[lineNumber].long_description, line);
        } else {
            strcat(locations[lineNumber].long_description, line);
        }
        
    } while (lineNumber != -1);

    #ifdef DEBUG_DATA_PARSING
    for(int i=0; i<NUM_LOCATIONS; i++) {
        printf("Location [%d]: '%s'\n", i, locations[i].long_description);
    }
    #endif

    free(line);
}

void loadShortLocationDescriptions(FILE *fp) {
    char *line = (char*)malloc(sizeof(char) * 100);
    int lineNumber = 0;

    do {
        fgets(line, 100, fp);
        lineNumber = trimEntryNumber(line);
        if(lineNumber == -1) {
            break;
        }

        trimLeading(line, 0);

        if(strlen(locations[lineNumber].short_description) == 0) {
            strcpy(locations[lineNumber].short_description, line);
        } else {
            strcat(locations[lineNumber].short_description, line);
        }
        
    } while (lineNumber != -1);

    #ifdef DEBUG_DATA_PARSING
    for(int i=0; i<NUM_LOCATIONS; i++) {
        printf("Short Location [%d]: '%s'\n", i, locations[i].short_description);
    }
    #endif

    free(line);
}

void loadTravelData(FILE *fp) {
    int ruleNumber = 0;
    int temp = 0;
    char *line = (char*)malloc(sizeof(char) * 50);

    do {
        fgets(line, 50, fp);
        sscanf(line, "%d %d %d %d %d %d %d %d %d %d\n",
            &travelRules[ruleNumber].from, &travelRules[ruleNumber].to,
            &travelRules[ruleNumber].verbs[0], &travelRules[ruleNumber].verbs[1],
            &travelRules[ruleNumber].verbs[2], &travelRules[ruleNumber].verbs[3],
            &travelRules[ruleNumber].verbs[4], &travelRules[ruleNumber].verbs[5],
            &travelRules[ruleNumber].verbs[6], &travelRules[ruleNumber].verbs[7]);
        
        if(travelRules[ruleNumber].from == -1) {
            break;
        }
        // printf("ruleNumber: [%d], From: [%d]\n", ruleNumber, travelRules[ruleNumber].from);
        
        
    } while (travelRules[ruleNumber++].from != -1 && temp++ < 300);

    #ifdef DEBUG_DATA_PARSING
    for(int i=0; i<NUM_TRAVEL_RULES; i++) {
        printf("From [%d] To [%d] By: [%d] [%d] [%d] [%d]\n", travelRules[i].from, travelRules[i].to,
            travelRules[i].verbs[0], travelRules[i].verbs[1], travelRules[i].verbs[2], travelRules[i].verbs[3]);
    }
    #endif
}

void loadWords(FILE *fp) {
    char *line = (char*)malloc(sizeof(char) * 100);
    int wordNumber = 0;
    int wordCount = 0;

    do {
        fgets(line, 100, fp);
        wordNumber = trimEntryNumber(line);
        if(wordNumber == -1) {
            break;
        }

        trimLeading(line, 0);

        words[wordCount].class = wordNumber / 1000;
        words[wordCount].number = wordNumber % 1000;
        strcpy(words[wordCount].text, line);
        wordCount++;
        
    } while (wordNumber != -1);

    #ifdef DEBUG_DATA_PARSING
    for(int i=0; i<NUM_WORDS; i++) {
        printf("Word class [%d]: '%s'\n", words[i].class, words[i].text);
    }
    #endif

    free(line);
}

void loadObjectDescriptions(FILE *fp) {
    char *line = (char*)malloc(sizeof(char) * 200);
    int i = 0, objectNumber = 0;

    do {
        fgets(line, 100, fp);
        objectNumber = trimEntryNumber(line);
        if(objectNumber == -1) {
            break;
        }

        trimLeading(line, 0);

        objectDescriptions[i].object = objectNumber % 100;
        objectDescriptions[i].state = objectNumber / 100;
        strcpy(objectDescriptions[i].text, line);
        i++;
        
    } while (objectNumber != -1);

    #ifdef DEBUG_DATA_PARSING
    for(int i=0; i<NUM_OBJECT_DESC; i++) {
        printf("Object [%d], State %d, Desc: '%s'\n", objectDescriptions[i].object,
                objectDescriptions[i].state, objectDescriptions[i].text);
    }
    #endif

    free(line);
}

void loadSpecials(FILE *fp) {
    char *line = (char*)malloc(sizeof(char) * 100);
    int lineNumber = 0;

    do {
        fgets(line, 100, fp);
        lineNumber = trimEntryNumber(line);
        if(lineNumber == -1) {
            break;
        }

        trimLeading(line, 1);

        if(strlen(randoms[lineNumber-1].description) == 0) {
            strcpy(randoms[lineNumber-1].description, line);
        } else {
            strcat(randoms[lineNumber-1].description, line);
        }
        
    } while (lineNumber != -1);

    #ifdef DEBUG_DATA_PARSING
    for(int i=0; i<NUM_LOCATIONS; i++) {
        printf("Random [%d]: '%s'\n", i, randoms[i].description);
    }
    #endif

    free(line);
}

// Gameplay
void run(void) {
    int yeah = 0;
    char *cmd1 = (char*)malloc(sizeof(char) * 100);
    char *cmd2 = (char*)malloc(sizeof(char) * 100);
    yes(65, 1, 0, &yeah); // Show initial message

    printMessage(1); // Show intro

    while(running) {
        printLocation(currentLocation);
        readCommand(cmd1, cmd2);
        if(strcmp(cmd1, "QUIT") == 0 || strcmp(cmd1, "Q") == 0) {
            running = 0;
            continue;
        }
        handleCommand(cmd1, cmd2);
        // printf("Full command: [%s] [%s]\n", cmd1, cmd2);
    }

    free(cmd1);
    free(cmd2);
}

void readSingleCommand(char *cmd) {
    fgets(cmd, 100, stdin);
    stripLinebreak(cmd);
    toUppercase(cmd);
}
void readCommand(char *cmd1, char* cmd2) {
    char *cmd = (char*)malloc(sizeof(char) * 100);
    readSingleCommand(cmd);
    // printf("Single: %s\n", cmd);
    if(containsSpace(cmd)) {
        sscanf(cmd, "%s %s", cmd1, cmd2);
    } else {
        strcpy(cmd1, cmd);
        cmd2[0] = '\0';
    }

    free(cmd);
}

void handleCommand(char *cmd1, char* cmd2) {
    Word *word1 = getWord(cmd1);
    Word *word2 = strlen(cmd2) > 0 ? getWord(cmd2) : NULL;

    if(word1 == NULL) {
        printMessage(60);
        return;
    }

    if(word1->class == WORD_DIR) {
        // printf("Direction word");
        if(strcmp(word1->text, "WEST") == 0) { // Special case
            printMessage(17);
        }
        handleTravel(word1);
    }
}

void handleTravel(Word *word) {
    for(int i=0; i<NUM_TRAVEL_RULES; i++) {
        if(travelRules[i].from == currentLocation) {
            for(int j=0; j<10; j++) {
                if(travelRules[i].verbs[j] == word->number) {
                    currentLocation = travelRules[i].to;
                    return;
                } else if(travelRules[i].verbs[j] == 0) {
                    break;
                }
            }
        }
    }

}

void yes(int messageToShow, int messageIfYes, int messageIfNo, int *hasSaidYes) {
    char *cmd = (char*)malloc(sizeof(char) * 100);
    printMessage(messageToShow);
    readSingleCommand(cmd);
    // printf("Command: [%s]\n", cmd);

    if(strcmp(cmd, "NO") == 0 || strcmp(cmd, "N") == 0) {
        *hasSaidYes = 0;
        if(messageIfNo) {
            printMessage(messageIfNo);
        }
    } else {
        *hasSaidYes = 1;
        if(messageIfYes) {
            printMessage(messageIfYes);
        }
    }
    free(cmd);
}

Word *getWord(const char *cmd) {
    for(int i=0; i<NUM_WORDS; i++) {
        if(strcmp(cmd, (*(words + i)).text) == 0) {
            return words + i;
        }
    }
    return NULL;
}

// Utils
void printMessage(int num) {
    printf("\n%s\n", randoms[num-1].description);
}
void printLocation(int num) {
    if(locations[num].visited) {
        printf("\n%s\n", locations[num].short_description);
    } else {
        locations[num].visited = 1;
        printf("\n%s\n", locations[num].long_description);
    }
}
