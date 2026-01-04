#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define DEBUG_DATA_PARSING 1

#define NUM_LOCATIONS 80
#define NUM_WORDS 500
#define NUM_TRAVEL_RULES 200
#define NUM_RANDOMS 80
#define NUM_OBJECT_DESC 23


typedef struct _location {
    char *long_description;
    char *short_description;
    int visited;
    int numObjectsHere;
    int objects[24];
} Location;

typedef enum {
    WORD_DIR = 0,
    WORD_NOUN = 1,
    WORD_VERB = 2,
    WORD_SPECIAL = 3
} WordClass;

typedef struct _word {
    WordClass class;
    int number;
    char *text;
} Word;

typedef struct _travelRule {
    int from;
    int to;
    int verbs[10];
} TravelRule;

typedef struct _random {
    char* description;
} Random;

typedef struct _object {
    int number;
    int state;
    char* text;
} ObjectDescriptions;

typedef enum {
    TYPE_OK = 0,
    TYPE_BLOCKED = 1,
    TYPE_AMBIGUOUS = 2,
    TYPE_INVALID = 3,
    TYPE_SPECIAL = 4
} MoveType;

typedef struct _moveResult {
    MoveType type;
    int dest;
    int messageNumber;
} MoveResult;

enum {
    KEYS = 1,
    LAMP = 2,
    GRATE = 3,
    CAGE = 4,
    ROD = 5,
    STEPS = 6,
    BIRD = 7,
    NUGGET = 10,
    SNAKE = 11,
    FISSURE = 12,
    DIAMOND = 13,
    SILVER = 14,
    JEWEL = 15,
    COINS = 16,
    DWARF = 17,
    ROCK = 18,
    FOOD = 19,
    WATER = 20,
    AXE = 21,
    KNIFE = 22,
    CHEST = 23
};

float RAN;
Location *locations;
Word *words;
TravelRule *travelRules;
Random *randoms;
ObjectDescriptions *objectDescriptions;
MoveResult *currentMove;

int setup;
int running = 1;
int currentLocation;
int objectState[NUM_OBJECT_DESC];

// initialisation
void init(void);
void readData(void);
void loadLongLocationDescriptions(FILE *fp);
void loadShortLocationDescriptions(FILE *fp);
void loadTravelData(FILE *fp);
void loadWords(FILE *fp);
void loadObjectDescriptions(FILE *fp);
void loadSpecials(FILE *fp);
void setObjectLocations(void);

// Gameplay
void run(void);
void readSingleCommand(char *cmd);
void readCommand(char *cmd1, char* cmd2);
void handleCommand(char *cmd1, char* cmd2);
void handleTravel(Word *word, MoveResult *currentMove);
void handleSpecial(int code);
Word *getWord(const char *cmd);
void questionPlayer(int messageToShow, int messageIfYes, int messageIfNo, int *hasSaidYes);
void placeObject(int object, int location);
void removeObject(int object, int location);

// Cleanup
void end(void);

// Utils
void printMessage(int num);
void printLocation(int num);
void printObject(int num);
void getObject(int number, ObjectDescriptions *target);
