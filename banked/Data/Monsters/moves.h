#ifndef MOVES_H
#define MOVES_H

#include <gb/gb.h>
#include "types.h"
#include "status.h"

// #define MAX_MOVES 22

enum ElementalMoveIndex {
  HURRICANE,
  DIVE_BOMB,
  UPDRAFT,
  AIR_SLASH,
  GUST,
  TREMOR,
  ROCK_THROW,
  HARDEN,
  UNDERMINE,
  DRILL,
  RECKLESS_SLAM,
  LANDSLIDE,
  FIRE_BREATH,
  FIRE_BALL,
  HEAT_UP,
  LIGHTER,
  DETONATE,
  HEAT_VENT,
  COOLDOWN,
  COMPOST,
  TOXIC_THORNS,
  VINE_WHIP,
  SNARE,
  POISON_DART,
  TOXIC_GAS,
  RUSH,
  CLAW,
  BRACE,
  COUNTER,
  ACCELERATE,
  FOCUS,
  WILD_CHARGE,
  HEAVY_BITE,
  FURIOUS_STRIKE,
  LIGHTNING_STRIKE,
  VOLT_CHARGE,
  SPARK,
  SMITE,
  CHARGE_UP,
  WATER_JET,
  SUBMERGE,
  WASH_OFF,
  ABSORB,
  WATER_DOWN,
  SWIFT_DIVE,
  POWER_STREAM,
  MAX_MOVES
};

typedef struct {
///GENERAL MOVE INFO
  enum ElementalMoveIndex index;
  char name[20];
  enum E_Type type;
  int power;
  double accuracy;
//////// STATUS CONDITION
  enum StatusConditionIndex statusCondition;
  double statusConditionChance;
//////// STAT CHANGE
//Attacker
  int attackerAtk;
  int attackerDef;
  int attackerSpd;
  int attackerHPperc;
  UBYTE clearAttackerDebuffs;
//Defender
  int defenderAtk;
  int defenderDef;
  int defenderSpd;
  int defenderHP;
  UBYTE clearDefenderPositiveBuff;
} Move;

extern const Move elementalMoves[MAX_MOVES];


#endif