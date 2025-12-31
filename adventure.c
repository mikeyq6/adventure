#include "adventure.h"
#include "utils.h"

int main(int argc, char **argv) {
    init();
    return 0;
}

void init(void) {
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

    
    
// C READ THE PARAMETERS

// 	IF(SETUP.NE.0) GOTO 1
// 	SETUP=1
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


// 	DATA(JSPKT(I),I=1,16)/24,29,0,31,0,31,38,38,42,42,43,46,77,71
// 	1 ,73,75/
// 	DATA(IPLT(I),I=1,20)/3,3,8,10,11,14,13,9,15,18,19,17,27,28,29
// 	1 ,30,0,0,3,3/
// 	DATA(IFIXT(I),I=1,20)/0,0,1,0,0,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0/
// 	DATA(DTRAV(I),I=1,15)/36,28,19,30,62,60,41,27,17,15,19,28,36
// 	1 ,300,300/
   
// 	DO 1001 I=1,300
// 	STEXT(I)=0
// 	IF(I.LE.200) BTEXT(I)=0
// 	IF(I.LE.100)RTEXT(I)=0
// 1001	LTEXT(I)=0
// 	I=1

    for(i=0; i<300; i++) {
        stext[i] = 0;
        if(i < 200) btext[i] = 0;
        if(i < 100) rtext[i] = 0;
        ltext[i] = 0;
    }
    i = 0;

    readData();
    // f1100(0);

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
        printf("Section: %d\n", section);
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
                loadSpecials(fp);
                break;
            case 6:
                loadSpecials(fp);
                break;
            case 0:
                section = -1;
                break;
        }
        
    }

    // 1002	READ(1,1003) IKIND
    // Read next char value
    // fgets(&ikind, 2, fp);
    // fscanf(fp, "%d", &ikind);
    // printf("Read: %d\n", ikind);

    // // 1003	FORMAT(G)
    // // format it to numeric

    // // 	GOTO(1100,1004,1004,1013,1020,1004,1004)(IKIND+1)
    // // Depending on the section number, call these subroutines
    // switch(ikind) {
    //     case 0:
    //         fclose(fp);
    //         return;
    //     case 1:
    //     case 2:
    //     case 5:
    //     case 6:
    //         f1004(fp);
    //         break;
    //     case 3:
    //         f1013();
    //         break;
    //     case 4:
    //         f1020();
    //         break;

    // }

// C TRAVEL = NEG IF LAST THIS SOURCE + DEST*1024 + KEYWORD

// C COND  = 1 IF LIGHT,  2 IF DON T ASK QUESTION
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

    for(int i=0; i<NUM_LOCATIONS; i++) {
        printf("Location [%d]: '%s'\n", i, locations[i].long_description);
    }

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

    for(int i=0; i<NUM_LOCATIONS; i++) {
        printf("Short Location [%d]: '%s'\n", i, locations[i].short_description);
    }

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

    for(int i=0; i<NUM_TRAVEL_RULES; i++) {
        printf("From [%d] To [%d] By: [%d] [%d] [%d] [%d]\n", travelRules[i].from, travelRules[i].to,
            travelRules[i].verbs[0], travelRules[i].verbs[1], travelRules[i].verbs[2], travelRules[i].verbs[3]);
    }
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
        strcpy(words[wordCount].text, line);
        wordCount++;
        
    } while (wordNumber != -1);

    // for(int i=0; i<NUM_WORDS; i++) {
    //     printf("Word class [%d]: '%s'\n", words[i].class, words[i].text);
    // }

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

        trimLeading(line, 0);
        // TODO
        
    } while (lineNumber != -1);

    // for(int i=0; i<NUM_LOCATIONS; i++) {
    //     printf("Short Location [%d]: '%s'\n", i, locations[i].short_description);
    // }

    free(line);

}

void f1004(FILE *fp) {
    short jkind;
    char sentence[100];

    fscanf(fp, "%hd", &jkind);
    fgets(sentence, sizeof sentence, fp);
    trimLeading(sentence, 1);
    printf("Read: '%hd', '%s'\n", jkind, sentence);

// 1004	READ(1,1005)JKIND,(LLINE(I,J),J=3,22)
// 1005	FORMAT(1G,20A5)
// 	IF(JKIND.EQ.-1) GOTO 1002
// 	DO 1006 K=1,20
// 	KK=K
// 	IF(LLINE(I,21-K).NE.' ') GOTO 1007
// 1006	CONTINUE
// 	STOP
// 1007	LLINE(I,2)=20-KK+1
// 	LLINE(I,1)=0
// 	IF(IKIND.EQ.6)GOTO 1023
// 	IF(IKIND.EQ.5)GOTO 1011
// 	IF(IKIND.EQ.1) GOTO 1008
// 	IF(STEXT(JKIND).NE.0) GOTO 1009
// 	STEXT(JKIND)=I
// 	GOTO 1010


// 1008	IF(LTEXT(JKIND).NE.0) GOTO 1009
// 	LTEXT(JKIND)=I
// 	GOTO 1010
// 1009	LLINE(I-1,1)=I
// 1010	I=I+1
// 	IF(I.NE.1000)GOTO 1004
// 	PAUSE 'TOO MANY LINES'

// 1011	IF(JKIND.LT.200)GOTO 1012
// 	IF(BTEXT(JKIND-100).NE.0)GOTO 1009
// 	BTEXT(JKIND-100)=I
// 	BTEXT(JKIND-200)=I
// 	GOTO 1010
// 1012	IF(BTEXT(JKIND).NE.0)GOTO 1009
// 	BTEXT(JKIND)=I
// 	GOTO 1010

// 1023	IF(RTEXT(JKIND).NE.0) GOTO 1009
// 	RTEXT(JKIND)=I
// 	GOTO 1010
}

void f1013(void) {
    // 1013	I=1
// 1014	READ(1,1015)JKIND,LKIND,(TK(L),L=1,10)
// 1015	FORMAT(12G)
// 	IF(JKIND.EQ.-1) GOTO 1002
// 	IF(KEY(JKIND).NE.0) GOTO 1016
// 	KEY(JKIND)=I
// 	GOTO 1017
// 1016	TRAVEL(I-1)=-TRAVEL(I-1)
// 1017	DO 1018 L=1,10
// 	IF(TK(L).EQ.0) GOTO 1019
// 	TRAVEL(I)=LKIND*1024+TK(L)
// 	I=I+1
// 	IF(I.EQ.1000) STOP
// 1018	CONTINUE
// 1019	TRAVEL(I-1)=-TRAVEL(I-1)
// 	GOTO 1014
}

void f1020(void) {

// 1020	DO 1022 IU=1,1000
// 	READ(1,1021) KTAB(IU),ATAB(IU)
// 1021	FORMAT(G,A5)
// 	IF(KTAB(IU).EQ.-1)GOTO 1002
// 1022	CONTINUE
// 	PAUSE 'TOO MANY WORDS'
}

void f1100(float val) {
// 1100	DO 1101 I=1,100
// 	IPLACE(I)=IPLT(I)
// 	IFIXED(I)=IFIXT(I)
// 1101	ICHAIN(I)=0

// 	DO 1102 I=1,300
// 	COND(I)=0
// 	ABB(I)=0
// 1102	IOBJ(I)=0
// 	DO 1103 I=1,10
// 1103	COND(I)=1
// 	COND(16)=2
// 	COND(20)=2
// 	COND(21)=2
// 	COND(22)=2
// 	COND(23)=2
// 	COND(24)=2
// 	COND(25)=2
// 	COND(26)=2
// 	COND(31)=2
// 	COND(32)=2
// 	COND(79)=2

// 	DO 1107 I=1,100
// 	KTEM=IPLACE(I)
// 	IF(KTEM.EQ.0)GOTO 1107
// 	IF(IOBJ(KTEM).NE.0) GOTO 1104
// 	IOBJ(KTEM)=I
// 	GO TO 1107
// 1104	KTEM=IOBJ(KTEM)
// 1105	IF(ICHAIN(KTEM).NE.0) GOTO 1106
// 	ICHAIN(KTEM)=I
// 	GOTO 1107
// 1106	KTEM=ICHAIN(KTEM)
// 	GOTO 1105
// 1107	CONTINUE
// 	IDWARF=0
// 	IFIRST=1
// 	IWEST=0
// 	ILONG=1
// 	IDETAL=0
// 	PAUSE 'INIT DONE'
}

