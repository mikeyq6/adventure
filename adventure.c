#include "adventure.h"

int main(int argc, char **argv) {
    init();
    return 0;
}

void init(void) {
    for(int i=0; i<100; i++) {
        ifixt[i] = 0;
    }
    
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
    jspkt[0] = 24;
    jspkt[1] = 29;
    jspkt[2] = 0;
    jspkt[3] = 31;
    jspkt[4] = 0;
    jspkt[5] = 31;
    jspkt[6] = 38;
    jspkt[7] = 38;
    jspkt[8] = 42;
    jspkt[9] = 42;
    jspkt[10] = 43;
    jspkt[11] = 46;
    jspkt[12] = 77;
    jspkt[13] = 71;
    jspkt[14] = 73;
    jspkt[15] = 75;

    iplt[0] = 3;
    iplt[1] = 3;
    iplt[2] = 8;
    iplt[3] = 10;
    iplt[4] = 11;
    iplt[5] = 14;
    iplt[6] = 13;
    iplt[7] = 9;
    iplt[8] = 15;
    iplt[9] = 18;
    iplt[10] = 19;
    iplt[11] = 17;
    iplt[12] = 27;
    iplt[13] = 28;
    iplt[14] = 29;
    iplt[15] = 30;
    iplt[15] = 0;
    iplt[15] = 0;
    iplt[15] = 3;
    iplt[15] = 3;

    ifixt[2] = 1;
    ifixt[5] = 1;
    ifixt[7] = 1;
    ifixt[8] = 1;
    ifixt[10] = 1;
    ifixt[11] = 1;

    dtrav[0] = 36;
    dtrav[1] = 28;
    dtrav[2] = 19;
    dtrav[3] = 30;
    dtrav[4] = 62;
    dtrav[5] = 60;
    dtrav[6] = 41;
    dtrav[7] = 27;
    dtrav[8] = 17;
    dtrav[9] = 15;
    dtrav[10] = 19;
    dtrav[11] = 28;
    dtrav[12] = 36;
    dtrav[13] = 300;
    dtrav[14] = 300;
    
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


// 1002	READ(1,1003) IKIND
// 1003	FORMAT(G)
// 	GOTO(1100,1004,1004,1013,1020,1004,1004)(IKIND+1)
// 1004	READ(1,1005)JKIND,(LLINE(I,J),J=3,22)
// 1005	FORMAT(1G,20A5)
// 	IF(JKIND.EQ.-1) GOTO 1002
// 	DO 1006 K=1,20
// 	KK=K
// 	IF(LLINE(I,21-K).NE.' ') GOTO 1007
// 1006	CONTINUE
// 	STOP
}
