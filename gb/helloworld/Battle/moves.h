#ifndef MOVES_H
#define MOVES_H

#include "types.h"

#define MAX_MOVES 30

enum ElementalMoveIndex {
FIREBALL,
FLAMETHROWER,
RAZOR_LEAF,
ROCK_SLIDE,
BUBBLE_BEAM,
EARTHQUAKE,
GALE,
THUNDERBOLT,
LEAF_BLADE,
THUNDERMOVE,
SURF,
ICE_BEAM,
SOLAR_BEAM,
HYDRO_PUMP,
BLIZZARD,
HYPER_BEAM,
DRAGON_BREATH,
PSYCHIC,
SHADOW_BALL,
IRON_HEAD,
DRAGON_PULSE,
MOONBLAST
};






const typedef struct {
    enum ElementalMoveIndex moveName;
    char name[20];
    ElementalType type;
    int power;
} Move;

extern const Move moves[MAX_MOVES];

#endif