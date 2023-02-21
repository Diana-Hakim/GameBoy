#ifndef SELECT_MONSTERS_H
#define SELECT_MONSTERS_H

#include <gb/gb.h>
#include <stdio.h>

#include "../MonsterInfo/monsters.c"
// #include "../MonsterInfo/moves.c"
#include "../Assests/Design/Backgrounds/Select/Select_Screen_data.c"
#include "../Assests/Design/Backgrounds/Select/Select_Screen_map.c"
#include "../Assests/Design/Sprites/Icons/Cursors.c"
#include <gb/console.h>
#include <gb/gb.h>

#define selected_options_count 6

void selectMonsters();

#endif