#ifndef BATTLE_H
#define BATTLE_H

#include "monsters.c"

#define MAX_PLAYER_MONSTERS 6

typedef struct {
    Monster *team[MAX_PLAYER_MONSTERS];
    int current_monster;
} Player;

void start_battle(Player *player1, Player *player2);

#endif