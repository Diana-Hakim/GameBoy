#include <gb/gb.h>
#include <stdio.h>
#include "Data/Monsters/types.h"
#include "Data/Monsters/moves.h"
#include "Data/Monsters/monsters.h"
#include "Data/Monsters/status.h"



int var_5;  /* In external RAM bank 3 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// BANK 5: MONSTERS ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////Types

const ElementalType ElementalTypes[] = {
  {FIRE, "Fire", {3/4, 5/4, 3/4, 1, 5/4, 1, 1}},
  {NATURE, "Nature", {0, 3/4, 5/4, 5/4, 3/4, 1, 1}},
  {EARTH, "Earth", {5/4, 0, 3/4, 5/4, 1, 3/4, 1}},
  {THUNDER, "Thunder", {1, 3/4, 0, 3/4, 5/4, 5/4, 1}},
  {AIR, "Air", {3/4, 5/4, 1, 0, 3/4, 5/4, 1}},
  {WATER, "Water", {5/4, 1, 5/4, 3/4, 0, 3/4, 1}},
  {NO_TYPE, "None", {1, 1, 1, 1, 1, 1, 1}}
};

///////////////////// Effects

const StatusCondition statusConditions[MAX_STATUS] = {
    {N_SC, "None", 0, FALSE, 0, 0, 0},
    {STUN, "Stun", 1, TRUE, 0, 0, 0},
    {POISON, "Poison", -1, FALSE, 8, -1, 0},
    {IGNITE, "Ignite", -1, FALSE, 8, 0, -1},
    {KNOCKUP, "Knockup", 2, FALSE, 4, 0, 0},
};


//////////////////////////// Moves

const Move elementalMoves[MAX_MOVES] = {
  {HURRICANE, "Hurricane",AIR, 50, 1, KNOCKUP, 1/2,              0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {DIVE_BOMB, "Dive Bomb", AIR, 90, 4/5, N_SC, 0,                0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {UPDRAFT, "Updraft", AIR, 0, 1, KNOCKUP, 1,                    0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {AIR_SLASH, "Air Slash", AIR, 45, 1, N_SC, 0,                  0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {GUST, "Gust", AIR, 35, 1, KNOCKUP, 1/5,                       0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {TREMOR, "Tremor", EARTH, 45, 1, N_SC, 0,                      0, 0, 0, 0, FALSE,     -1, 0, 0, 0, FALSE },
  {ROCK_THROW, "Rock Throw", EARTH, 60, 1, N_SC, 0,              0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {HARDEN, "Harden", EARTH, 0, 1, N_SC, 0,                       0, 2, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {UNDERMINE, "Undermine", EARTH, 60, 1, N_SC, 4/5,              0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {DRILL, "Drill", EARTH, 0, 1, N_SC, 1/4,                       0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {RECKLESS_SLAM, "Reckless Slam", EARTH, 100, 1, N_SC, 4/5,     0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {LANDSLIDE, "Landslide", EARTH, 80, 1, N_SC, 0,                0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {FIRE_BREATH, "Fire Breath", FIRE, 60, 1, IGNITE, 1/3,         0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {FIRE_BALL, "Fire Ball", FIRE, 75, 1, IGNITE, 3/20,            0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {HEAT_UP, "Heat Up", FIRE, 0, 1, N_SC, 0,                      2, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {LIGHTER, "Lighter", FIRE, 0, 1, IGNITE, 1,                    0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {DETONATE, "Detonate", FIRE, 150, 1, N_SC, 1,                  0, 0, 0, -150, FALSE,   0, 0, 0, 0, FALSE },
  {HEAT_VENT, "Heat Vent", FIRE, 110, 1, N_SC, 9/10,             0, -1, 0, 0, FALSE,     0, 0, 1, 0, FALSE },
  {COOLDOWN, "Cooldown", FIRE, 0, 1, N_SC, 0,                   -1, 2, 0, 0, FALSE,     -1, 0, 0, 0, FALSE },
  {COMPOST, "Compost", NATURE, 0, 1, N_SC, 0,                    0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {TOXIC_THORNS, "Toxic Thorns", NATURE, 35, 1, POISON, 1,       0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {VINE_WHIP, "Vine Whip", NATURE, 50, 1, N_SC, 1,               0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {SNARE, "Snare", NATURE, 40, 1, N_SC, 1,                       0, 0, 0, 0, FALSE,      0, -1, 0, 0, FALSE },
  {POISON_DART, "Poison Dart", NATURE, 40, 1, POISON, 1/2,       0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {TOXIC_GAS, "Toxic Gas", NATURE, 0, 1, POISON, 1,              0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {RUSH, "Rush", NO_TYPE, 50, 1, N_SC, 1,                        0, 0, 1, 0, FALSE,      0, 0, 0, 0, FALSE },
  {CLAW, "Claw", NO_TYPE, 65, 1, N_SC, 1/10,                     0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {BRACE, "Brace", NO_TYPE, 0, 1, N_SC, 0,                       1, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {COUNTER, "Counter", NO_TYPE, 30, 1, N_SC, 0,                1, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {ACCELERATE, "Accelerate", NO_TYPE, 0, 1, N_SC, 0,             0, 0, 2, 0, FALSE,      0, 0, 0, 0, FALSE },
  {FOCUS, "Focus", NO_TYPE, 0, 1, N_SC, 0,                     0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {WILD_CHARGE, "Wild Charge", NO_TYPE, 80, 1, N_SC, 0,          0, 0, 0, 0, TRUE,       0, 0, 0, 0, FALSE },
  {HEAVY_BITE, "Heavy Bite", NO_TYPE, 75, 1, N_SC, 0,          0, 1, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {FURIOUS_STRIKE, "Furious Strike", THUNDER, 50, 1, IGNITE,   1/2, 0, 0, 0, 0, FALSE,   0, 0, 0, 0, FALSE },
  {LIGHTNING_STRIKE, "Lightning Strike", THUNDER, 75, 1, STUN, 1/10, 0, 0, -1, 0, FALSE,  0, 0, 0, 0, FALSE },
  {VOLT_CHARGE, "Volt Charge", THUNDER, 80, 1, STUN, 1/2,        0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {SPARK, "Spark", THUNDER, 40, 1, STUN, 3/20,                   0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {SMITE, "Smite", THUNDER, 80, 1, STUN, 1/4,                   0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {CHARGE_UP, "Charge Up", THUNDER, 0, 1, N_SC, 0,             2, -1, 0, 0, FALSE,     0, 0, 0, 0, FALSE },
  {WATER_JET, "Water Jet", WATER, 80, 1, N_SC, 0,              0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {SUBMERGE, "Submerge", WATER, 50, 1, N_SC, 0,                0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {WASH_OFF, "Wash Off", WATER, 0, 1, N_SC, 0,                 0, 0, 0, 0, FALSE,      0, 0, 0, 1, FALSE },
  {ABSORB, "Absorb", WATER, 0, 1, N_SC, 0,                     0, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE },
  {WATER_DOWN, "Water Down", WATER, 0, 1, N_SC, 0,              0, 1, 0, 0, TRUE,       0, 0, 0, 0, FALSE },
  {SWIFT_DIVE, "Swift Dive", WATER, 50, 1, N_SC, 0,            0, 0, 1, 0, FALSE,      0, 0, 0, 0, FALSE }, 
  {POWER_STREAM, "Power Stream", WATER, 65, 1, N_SC, 0,        1, 0, 0, 0, FALSE,      0, 0, 0, 0, FALSE }
};

///////////////////// Monsters

const Monster monsters[MAX_MONSTERS] = {
    {LAVOTTER, "Lavotter", {FIRE, FIRE}, {FIRE_BREATH, HEAT_UP, RUSH, CLAW}, 90, 50,110,100 },
    {THORNTRUNK,"Thorntrunk",{NATURE, NATURE},{VINE_WHIP, COMPOST, COUNTER, TREMOR},100,75,75,60},
    {TBD1,"TBD1",{EARTH, EARTH},{LANDSLIDE, UNDERMINE, ACCELERATE, FOCUS}, 80, 80, 70, 90},
    {SHOCKTOPUS, "Shocktopus",{WATER, THUNDER},{WATER_JET, SUBMERGE, VOLT_CHARGE, CHARGE_UP}, 60, 50, 120, 80},
    {TBD2,"TBD2",{WATER, WATER},{WATER_JET, SWIFT_DIVE, ABSORB, ACCELERATE}, 70, 70, 70, 80},
    {BOLTOSAUR, "Boltosaur", {THUNDER, THUNDER}, {SMITE, VOLT_CHARGE, RUSH, BRACE}, 80, 80, 90, 50},
    {TBD3, "TBD3",{NO_TYPE, NO_TYPE},{AIR_SLASH, POISON_DART, COUNTER, WILD_CHARGE},75, 120, 60, 60},
    {TBD4, "TBD4", {WATER, NATURE}, {SNARE, WATER_DOWN, COMPOST, POWER_STREAM}, 75, 50, 100, 80},
    {TBD5, "TBD5",{EARTH, FIRE},{FIRE_BALL, DETONATE, HARDEN, RECKLESS_SLAM},90, 100, 150, 40},
    {TBD6, "TBD6",{FIRE, AIR}, {AIR_SLASH, FIRE_BREATH, HEAT_UP, CLAW}, 50, 70, 80, 90},
    {TBD7, "TBD7", {EARTH, NO_TYPE}, {SNARE, ROCK_THROW, CLAW, WATER_DOWN}, 90, 120, 60, 40},
    {TBD8, "TBD8", {AIR, NO_TYPE},{DIVE_BOMB, UPDRAFT, ACCELERATE, RUSH},70,70,70,130},
    {TBD9, "TBD9",{NO_TYPE, NO_TYPE},{AIR_SLASH, CLAW, COUNTER, COOLDOWN},75,85,75,55},
    {TBD10, "TBD10",{FIRE, AIR},{AIR_SLASH, FIRE_BREATH, HEAT_UP, CLAW},50,70,80,90},
    {TBD11, "TBD11", {EARTH, NO_TYPE},{SNARE, ROCK_THROW, CLAW, WATER_DOWN},90,60,90,40},
    {TBD12, "TBD12",{AIR, NO_TYPE},{DIVE_BOMB, UPDRAFT, ACCELERATE, RUSH},70,70,70,130},
    {TBD13, "TBD13", {NO_TYPE, NO_TYPE}, {AIR_SLASH, CLAW, COUNTER, COOLDOWN}, 75, 85, 75, 55},
    {TBD14, "TBD14", {AIR, NATURE}, {HURRICANE, TOXIC_THORNS, RUSH, UPDRAFT}, 50, 65, 85, 75},
    {TBD15, "TBD15", {EARTH, WATER},{DRILL, UNDERMINE, SWIFT_DIVE, ACCELERATE}, 115, 50, 65, 85},
    {TBD16, "TBD16", {AIR, NO_TYPE}, {GUST, RUSH, UPDRAFT, BRACE}, 80, 70, 100, 50},
    {TBD17, "TBD17", {THUNDER, NO_TYPE},{SNARE, LIGHTNING_STRIKE, CHARGE_UP, FOCUS}, 65,50, 100, 70},
    {TBD18, "TBD18",{NO_TYPE, NO_TYPE},{WILD_CHARGE, TREMOR, HEAVY_BITE, BRACE},90,60,120,90},
    {TBD19, "TBD19", {NATURE, NO_TYPE},{TOXIC_THORNS, TOXIC_GAS, BRACE, HEAVY_BITE},75,80,60,75},
    {TBD20, "TBD20",{FIRE, THUNDER},{FURIOUS_STRIKE, FOCUS, CLAW, SPARK}, 60, 45,120, 80},
    {TBD21, "TBD21",{WATER, NO_TYPE},{WASH_OFF, POWER_STREAM, TOXIC_GAS, GUST}, 100, 70, 50, 50},
    {TBD22, "TBD22",{FIRE, NO_TYPE}, {HEAT_VENT, LIGHTER, FIRE_BALL, GUST},100, 70, 50, 50}
};






// void bank_5() NONBANKED /* In ROM bank 3 */
// {
//   // puts("I'm in ROM bank 5     ");
// }
