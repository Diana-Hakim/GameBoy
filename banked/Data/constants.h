#ifndef CONSTANTS_H
#define CONSTANTS_H

/// GENERAL
#define BIT 8

/// PRINTING LOCATION
#define BACKGROUND_START 37 // WITH FONT
// #define Y_START_LINE 0
#define Y_LAST_LINE 17
#define X_STATS 14
#define DEVICE_SCREEN_WIDTH 20
#define DEVICE_SCREEN_HEIGHT 18

// #define HALF_BIT 4

//// NAVIGATION
#define WALL 0x25
#define MAX_CPU 4
#define MAX_BATTLE_CPU 4

// LOCATION
#define OFF_SCREEN_XY  (UINT8)200
#define LEFT_X         (UINT8)40
#define MIDDLE_X       (UINT8)80
#define RIGHT_X        (UINT8)120
#define TOP_Y          (UINT8)50
#define MIDDLE_Y       (UINT8)78
#define BOTTOM_Y       (UINT8)120

///// MONSTERS / MOVE / TYPES
#define MAX_TEAM 6
#define NO_MONSTER -1
#define MAX_MONSTER_MOVES 4
#define MAX_MONSTER_TYPES 2
#define MAX_DIALOG_LENGTH 50


#endif // CONSTANTS_H