#ifndef TYPES_H
#define TYPES_H

#define MAX_TYPES 7

enum E_Type {
  FIRE,
  NATURE,
  EARTH,
  THUNDER,
  AIR,
  WATER,
  NO_TYPE
};

typedef struct {
  enum E_Type etype;
  char name[20];
  double effectivness[MAX_TYPES];
} ElementalType;

extern const ElementalType ElementalTypes[MAX_TYPES];

#endif