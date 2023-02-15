#include <gb/gb.h>

//#include "../Background/Rooms/RoomInfo.h"


//const UINT8 GameCharacterHW = 16;
#define MAX_CPU 4

UBYTE spritesize = 8;

typedef enum {
  MAP_TOP = 50,
  MAP_BOTTOM = 120,
  MIDDLE_X = 80,
  MIDDLE_Y = 78
} SpawnPoint;



enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

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
};

struct CPU {
    struct GameCharacter base;
    char* dialog;
    UBYTE isBattleCPU;
};

////// TODO: MAKE A BATTLE CPU 
// struct BattleCPU {
// struct CPU cpu;
// bool isDefeated;
// 
// char* isDefeatedDialog;
// monsters team[]
// };


struct CPU_List {
    struct CPU characters[MAX_CPU];
    UINT8 count;
};


const struct CPU_List CPU_info = {
    {
        {
            {{0, 1, 2, 3}, 120, 50, 0, DOWN},   // base
            "Hello, I'm a CPU!",                   // dialog
            0                                    // isBattleCPU
        },
        {
            {{0, 1, 2, 3}, MIDDLE_X, MIDDLE_Y, 0, DOWN},   // base
            "Let's battle!",                       // dialog
            1                                     // isBattleCPU
        },
        {
            {{0, 1, 2, 3}, 120, 50, 0, DOWN},   // base
            "You won't beat me!",                  // dialog
            1                                     // isBattleCPU
        },
        {
            {{0, 1, 2, 3}, MIDDLE_X, 70, 0, DOWN},   // base
            "Get ready!",                           // dialog
            1                                     // isBattleCPU
        },
    },
    MAX_CPU
};