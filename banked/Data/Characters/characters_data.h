#ifndef CONSTANTSNAV_H
#define CONSTANTSNAV_H
#include <gb/gb.h>

#define playerGirlBank 2

typedef enum {
    DOWN = 0,
    UP = 1,
    LEFT = 2,
    RIGHT = 3,
    MAX_DIRECTIONS = 4
} direction;

typedef struct  {
    UBYTE spriteID[4];
    UINT8 spriteIndex;
    UINT8 spawnRoomNumber; 
    UINT8 x;
    UINT8 y;
    UINT16 tileLocation;
    direction facing_direction;
    UINT8 team[6]; 
} GameCharacter;


typedef struct {
    char initDialog[51]; // Fixed-length array with space for 50 characters plus null terminator
    char finalDialog[51]; // Fixed-length array with space for 50 characters plus null terminator
    char name[21]; 
    GameCharacter base;
} BattleCPU;



#endif
/* End of PLAYERGIRL.H */
