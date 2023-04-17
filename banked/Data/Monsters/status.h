#ifndef STATUS_H
#define STATUS_H

#include <gb/gb.h>


enum StatusConditionIndex {
  N_SC,
  STUN,
  POISON,
  IGNITE,
  KNOCKUP,
  MAX_STATUS // This should always be last
};

typedef struct {
  enum StatusConditionIndex index;
  char name[20];
  int duration;  // How many turns the condition lasts
  UBYTE removesTurn; // If true, the monster loses its next turn
  int damage; // The amount of damage the monster takes at the end of each turn
  int speedModifier; // The amount of speed the monster loses while affected
  int defenseModifier; // The amount of defense the monster loses while affected
} StatusCondition;

extern const StatusCondition statusConditions[MAX_STATUS];


#endif