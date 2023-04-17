#include "common.h"

UINT8 wait;

void clearScreen() {
    UINT8 i, j;
    for (i = 0; i < 18; i++) {
        for (j = 0; j < 20; j++) {
            gotoxy(j, i);
            printf("%c", 0x00);
        }
    }
    gotoxy(0, 0);
}

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void printPaddedNumber(int num, int length) {
    int i;
    int numDigits;
    int numSpaces;
    int temp = num;
    numDigits = 0;
    while (temp != 0) {
        temp /= 10;
        numDigits++;
    }
    numSpaces = length - numDigits;
    if (numSpaces > 0) {
        for (i = 0; i < numSpaces; i++) {
            printf(" ");
        }
    }
    printf("%d", num);
}

void printPaddedString(char* str, int length) {
    int i;
    int strLength = strlen(str);
    int numSpaces = length - strLength;
    printf("%s", str);
    if (numSpaces > 0) {
        for (i = 0; i < numSpaces; i++) {
            printf(" ");
        }
    }
}


void fadeout(UINT8 time){
    for(wait=0;wait<4;wait++){
        switch(wait){
            case 0:
                BGP_REG = 0xE4;
                break;
            case 1:
                BGP_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xFE;
                break;
            case 3:
                BGP_REG = 0xFF;    
                break;                      
        }
        performantdelay(time);
    }
}

void fadein(UINT8 time){
    for(wait=0;wait<3;wait++){
        switch(wait){
            case 0:
                BGP_REG = 0xFE;
                break;
            case 1:
                BGP_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xE4;
                break;                  
        }
        performantdelay(time);
    }
}


// UINT16 convert_tile_index(UINT8 x, UINT8 y) {
//     UINT16 indexTLxl = (x - 8) / 8;
//     UINT16 indexTLyl = (y - 16) / 8;
//     return 20 * indexTLyl + indexTLxl;
// }
