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
    int effectivness[MAX_TYPES];
} ElementalType;

const ElementalType ElementalTypes[] = {
{FIRE, "Fire", {50, 150, 50, 100, 150, 0, 100}},
{NATURE, "Nature", {0, 50, 150, 150, 50, 100, 100}},
{EARTH, "Earth", {150, 0, 50, 150, 100, 50, 100}},
{THUNDER, "Thundr", {100, 50, 0, 50, 150, 150, 100}},
{AIR, "Air", {50, 150, 100, 0, 50, 150, 100}},
{WATER, "Water", {150, 100, 150, 50, 0, 50, 100}},
{NO_TYPE, "None", {100, 100, 100, 100, 100, 100, 100}}
};


#endif