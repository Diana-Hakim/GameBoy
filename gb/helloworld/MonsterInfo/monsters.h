#ifndef MONSTERS_H
#define MONSTERS_H

#include "types.h"
#include "moves.h"


#define MAX_MONSTERS 26




enum MonsterIndex {
CHARMANDER,
SQUIRTLE,
BULBASAUR,
DRAGONITE,
ALAKAZAM,
GARDEVOIR,
CHARIZARD,
BLASTOISE,
VENUSAUR,
GOLEM,
CHARMANDER2,
SQUIRTLE2,
BULBASAUR2,
DRAGONITE2,
ALAKAZAM2,
GARDEVOIR2,
CHARIZARD2,
BLASTOISE2,
VENUSAUR2,
GOLEM2,
GARDEVOIR3,
CHARIZARD3,
BLASTOISE3,
VENUSAUR3,
GOLEM3,
CHARMANDER3
};


typedef struct {
    enum MonsterIndex index;
    char name[20];
    enum Type types[2];
    enum ElementalMoveIndex moves[4];
    int health;
    int attack;
    int speed;
    int defense;
} Monster;


extern const Monster monsters[MAX_MONSTERS];


typedef enum StatusCondition {
    NONE,
    POISON,
    BURN,
    PARALYSIS,
    FREEZE,
    SLEEP
} StatusCondition;


// extern Monster monsters[MAX_MONSTERS]; // 25 monsters 

// typedef struct {
//     enum MonsterIndex monsterIndex; // monster type
//     int health;                     // current health 
//     StatusCondition status;         // status condition
//     int attackModifier;             // attack change
//     int defenseModifier;            // def change
//     int speedModifier;              // speed change
// } ActiveMonster;



// ActiveMonster createActiveMonster(enum MonsterIndex monsterIndex) {
//     ActiveMonster activeMonster = {
//         monsterIndex,
//         monsters[monsterIndex].health,
//         None,
//         0,
//         0,
//         0
//     };

//     return activeMonster;
// }

#endif

