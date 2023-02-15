#include "battle.h"
#include <stdio.h>

void start_battle(Player *player1, Player *player2) {
    while (1) {
        Monster *current_monster1 = player1->team[player1->current_monster];
        Monster *current_monster2 = player2->team[player2->current_monster];
        if (current_monster1->health <= 0) {
            printf("Player 1 monster %s fainted\n", current_monster1->name);
            player1->current_monster++;
            if (player1->current_monster >= MAX_PLAYER_MONSTERS) {
                printf("Player 2 wins the battle!\n");
                break;
            }
            continue;
        }
        if (current_monster2->health <= 0) {
            printf("Player 2 monster %s fainted\n", current_monster2->name);
            player2->current_monster++;
            if (player2->current_monster >= MAX_PLAYER_MONSTERS) {
                printf("Player 1 wins the battle!\n");
                break;
            }
            continue;
        }
        printf("%s (HP %d) vs %s (HP %d)\n", current_monster1->name, current_monster1->health,
               current_monster2->name, current_monster2->health);
        // You can add code here to make the monsters attack each other
    }
}
