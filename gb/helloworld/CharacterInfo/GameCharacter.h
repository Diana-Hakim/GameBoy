#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <gb/gb.h>
#include "../MonsterInfo/monsters.h"
#include "../MonsterInfo/moves.h"

#define MAX_CPU 4

typedef enum {
  MAP_TOP = 50,
  MAP_BOTTOM = 120,
  MIDDLE_X = 80,
  MIDDLE_Y = 78,
  OFF_SCREEN_XY = 200
} SpawnPoint;

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


UBYTE spritesize = 8;


struct GameCharacter {
    UBYTE spritids[4];
    UINT8 x;
    UINT8 y;
    UINT16 tileLocation;
   enum direction facing_direction;
};


struct Player {
    struct GameCharacter base;
    UINT8 numberCPUDefeated;
    enum MonsterIndex team[6]; /// SELECTED TEAM 
};

struct BaseCPU {
    struct GameCharacter base;
    char* dialog;
    UBYTE isBattleCPU;
};

struct CPU {
    struct BaseCPU base;
};

struct BattleCPU{
    struct BaseCPU base;
    enum MonsterIndex team[6]; 
    UBYTE isDefeated;
    char* defeatedDialog;
};


struct CPU_List {
    struct BaseCPU characters[MAX_CPU];
    UINT8 count;
};

