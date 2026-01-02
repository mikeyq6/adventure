#include <stdio.h>

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

typedef struct _objectText {
    int object;
    int state;
    char* text;
} ObjectText;

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

// C ADVENTURES
	// IMPLICIT INTEGER(A-Z)
	// REAL RAN
	// COMMON RTEXT,LLINE
	// DIMENSION IOBJ(300),ICHAIN(100),IPLACE(100)
	// 1 ,IFIXED(100),COND(300),PROP(100),ABB(300),LLINE(1000,22)
	// 2 ,LTEXT(300),STEXT(300),KEY(300),DEFAULT(300),TRAVEL(1000)
	// 3 ,TK(25),KTAB(1000),ATAB(1000),BTEXT(200),DSEEN(10)
	// 4 ,DLOC(10),ODLOC(10),DTRAV(20),RTEXT(100),JSPKT(100)
	// 5 ,IPLT(100),IFIXT(100)
 	// SETUP=1
    // 	KEYS=1
    // 	LAMP=2
    // 	GRATE=3
    // 	ROD=5
    // 	BIRD=7
    // 	NUGGET=10
    // 	SNAKE=11
    // 	FOOD=19
    // 	WATER=20
    // 	AXE=21


float RAN;
Location *locations;
Word *words;
TravelRule *travelRules;
Random *randoms;
ObjectText *objectDescriptions;
MoveResult *currentMove;
int iobj[300], ichain[100], iplace[100], ifixed[100], cond[300];
int prop[100], abb[300], lline[1000][22], ltext[300], stext[300];
int key[300], Default[300], travel[1000], tk[25], ktab[1000], atab[1000];
int btext[200], dseen[10], dloc[10], odloc[10], dtrav[20], rtext[100];
int jspkt[100], iplt[100], ifixt[100];

int setup, keys, lamp, grate, rod, bird, nugget, snake, food, water, axe;
int running = 1;
int currentLocation;

// initialisation
void init(void);
void readData(void);
void loadLongLocationDescriptions(FILE *fp);
void loadShortLocationDescriptions(FILE *fp);
void loadTravelData(FILE *fp);
void loadWords(FILE *fp);
void loadObjectDescriptions(FILE *fp);
void loadSpecials(FILE *fp);

// Gameplay
void run(void);
void readSingleCommand(char *cmd);
void readCommand(char *cmd1, char* cmd2);
void handleCommand(char *cmd1, char* cmd2);
void handleTravel(Word *word, MoveResult *currentMove);
void handleSpecial(int code);
Word *getWord(const char *cmd);
void yes(int messageToShow, int messageIfYes, int messageIfNo, int *hasSaidYes);

// Cleanup
void end(void);

// Utils
void printMessage(int num);
void printLocation(int num);
