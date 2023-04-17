#ifndef MONSTERS_H
#define MONSTERS_H

#include <gb/gb.h>
#include <string.h>
// #include <stdlib.h>
#include "moves.h"
#include "types.h"



#define MAX_TEAM_SIZE 6

enum MonsterIndex {
    LAVOTTER,
    THORNTRUNK,
    TBD1,
    SHOCKTOPUS,
    TBD2,
    BOLTOSAUR,
    TBD3,
    TBD4,
    TBD5,
    TBD6,
    TBD7,
    TBD8,
    TBD9,
    TBD10,
    TBD11,
    TBD12,
    TBD13,
    TBD14,
    TBD15,
    TBD16,
    TBD17,
    TBD18,
    TBD19,
    TBD20,
    TBD21,
    TBD22,
    MAX_MONSTERS
};




typedef struct {
  enum MonsterIndex index;
  char name[20];
  enum E_Type types[2];
  enum ElementalMoveIndex monsterMoves[4];
  int health;
  int attack;
  int speed;
  int defense;
} Monster;




typedef struct {
  enum MonsterIndex index;
  int hpModifier;
  enum StatusConditionIndex statusModifier;
} MonsterInstance;



typedef struct {
  Monster monsters[MAX_TEAM];
} Team;

typedef struct {
  Monster monsterType;
  int currentHP;
  int currentAttack;
  int currentDefense;
  int currentSpeed;
  enum StatusConditionIndex statusCondition; // new property for status condition
  int statusDuration; // how many turns the status lasts
  int statusRemovesTurn; // if true, the monster loses its next turn
  double statusDamage; // the amount of damage the monster takes at the end of each turn
  int statusSpeedModifier; // the amount of speed the monster loses while affected
  int statusDefenseModifier; // the amount of defense the monster loses while affected
} AttackMonster;


extern const Monster monsters[MAX_MONSTERS];

#endif // MONSTERS_H



