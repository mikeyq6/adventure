#include <stdio.h>

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
int iobj[300], ichain[100], iplace[100], ifixed[100], cond[300];
int prop[100], abb[300], lline[1000][22], ltext[300], stext[300];
int key[300], Default[300], travel[1000], tk[25], ktab[1000], atab[1000];
int btext[200], dseen[10], dloc[10], odloc[10], dtrav[20], rtext[100];
int jspkt[100], iplt[100], ifixt[100];

int setup, keys, lamp, grate, rod, bird, nugget, snake, food, water, axe;
int i;


void init(void);
void readData(void);
void f1004(FILE *fp);
void f1013(void);
void f1020(void);
void f1100(float val);
