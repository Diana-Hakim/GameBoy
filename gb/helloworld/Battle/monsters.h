#ifndef MONSTERS_H
#define MONSTERS_H

//#include "types.h"
// #include "moves.h"
#include "moves.h"

#define MAX_MONSTERS 20

typedef struct {
    char name[20];
    enum Type types[2];
    enum ElementalMoveIndex moves[4];
    int health;
    int attack;
    int speed;
    int defense;
} Monster;

extern Monster monsters[MAX_MONSTERS];

#endif

