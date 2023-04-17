#include <gb/gb.h>
#include <stdio.h>
#include <gb/console.h>
#include "Data/Background/BattleScreen_data.h"
#include "Data/Background/BattleScreen_map.h"
#include "Data/constants.h"
#include "Data/Monsters/monsters.h"

#define KBLU  "\x1B[34m"
#define KRED  "\x1B[31m"
#define KWHT  "\x1B[37m"

int var_4;  /* In external RAM bank 3 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// BANK 4: BATTLE SCREEN ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void bank_4() NONBANKED /* In ROM bank 3 */
// {
//   //gotoxy(0,18-6);
//   set_bkg_data(37, 36, BattleScreen_data); 
//   set_bkg_tiles(0,0,DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, BattleScreen_map);
//   // printf("BATTLE \n");
//   SWITCH_ROM_MBC1(2);
// }



void print_health_bar(AttackMonster *monster) {
  int health_percent = monster->currentHP * 100 / monster->monsterType.health;
  printf("%s: \t\t[", monster->monsterType.name);
  for (int i = 0; i < 20; i++) {
    if (i < health_percent / 5) {
      printf("#");
    } else {
      printf("-");
    }
  }
  printf("] %d/%d\n", monster->currentHP, monster->monsterType.health);
}

/////////////////////////////////////////////////////
void switch_out(AttackMonster *current_monster, Team *team) {
  int current_index;
  do {
    current_index = rand() % team->size; // choose a random index from the team
  } while (team->monstersA[current_index].currentHP <=
           0); // make sure the chosen monster is alive
  AttackMonster *new_monster = &team->monstersA[current_index];
  printf("%s, switch out!\n", current_monster->monsterType.name);
  printf("Go, %s!\n", new_monster->monsterType.name);
  // swap the two monsters in the team array
  AttackMonster temp = *current_monster;
  *current_monster = *new_monster;
  *new_monster = temp;
}

void apply_stat_change(AttackMonster *monster, enum StatIndex stat,
                       int change) {
  switch (stat) {
  case ATK:
    monster->currentAttack += change;
    if (monster->currentAttack < 0) {
      monster->currentAttack = 0;
    }
    printf("%s's attack changed by %d. New attack: %d\n",
           monster->monsterType.name, change, monster->currentAttack);
    break;
  case DEF:
    monster->currentDefense += change;
    if (monster->currentDefense < 0) {
      monster->currentDefense = 0;
    }
    printf("%s's defense changed by %d. New defense: %d\n",
           monster->monsterType.name, change, monster->currentDefense);
    break;
  case SPD:
    monster->currentSpeed += change;
    if (monster->currentSpeed < 0) {
      monster->currentSpeed = 0;
    }
    printf("%s's speed changed by %d. New speed: %d\n",
           monster->monsterType.name, change, monster->currentSpeed);
    break;
  case HP:
    monster->currentHP += change;
    if (monster->currentHP < 0) {
      monster->currentHP = 0;
    } else if (monster->currentHP > monster->monsterType.health) {
      monster->currentHP = change - (monster->currentHP);
    }
    printf("%s's HP changed by %d. New HP: %d\n", monster->monsterType.name,
           change, monster->currentHP);
    break;
  default:
    printf("Invalid stat index.\n");
    break;
  }
}

int prompt_move_selection(AttackMonster *current_monster) {
  int selected_move_index = -1;
  while (selected_move_index < 0 || selected_move_index >= 4) {
    printf("Select a move:\n");
    for (int i = 0; i < 4; i++) {
      printf("%d: %s\n", i + 1,
             elementalMoves[current_monster->monsterType.monsterMoves[i]].name);
    }
    printf("> ");
    scanf("%d", &selected_move_index);
    selected_move_index--;
    if (selected_move_index < 0 || selected_move_index >= 4) {
      printf("Invalid move selection.\n");
    }
  }
  // Map the user input to the index of the selected move in the monster's
  // moveset
  system("clear");
  return current_monster->monsterType.monsterMoves[selected_move_index];
}

void apply_status_condition(AttackMonster *monster, const StatusCondition *condition) {
  printf("Status Condition: %s\n", condition->name);
  monster->statusCondition = condition->index;
  monster->statusDuration = condition->duration;
  monster->statusRemovesTurn = condition->removesTurn;
  monster->statusDamage = condition->damage;
  monster->statusSpeedModifier = condition->speedModifier;
  monster->statusDefenseModifier = condition->defenseModifier;
}

void clear_positive_buffs(AttackMonster *defender) {
  if (defender->currentAttack > defender->monsterType.attack) {
    defender->currentAttack = defender->monsterType.attack;
  }
  if (defender->currentDefense > defender->monsterType.defense) {
    defender->currentDefense = defender->monsterType.defense;
  }
  if (defender->currentSpeed > defender->monsterType.speed) {
    defender->currentSpeed = defender->monsterType.speed;
  }
  if (defender->currentHP > defender->monsterType.health) {
    defender->currentHP = defender->monsterType.health;
  }
}

void clear_debuffs(AttackMonster *attacker) {
  if (attacker->currentAttack < attacker->monsterType.attack) {
    attacker->currentAttack = attacker->monsterType.attack;
    printf("%s's attack returned to normal!\n", attacker->monsterType.name);
  }
  if (attacker->currentDefense < attacker->monsterType.defense) {
    attacker->currentDefense = attacker->monsterType.defense;
    printf("%s's defense returned to normal!\n", attacker->monsterType.name);
  }
  if (attacker->currentSpeed < attacker->monsterType.speed) {
    attacker->currentSpeed = attacker->monsterType.speed;
    printf("%s's speed returned to normal!\n", attacker->monsterType.name);
  }
}

double calculate_effectiveness(AttackMonster *defender, Move move) {
  double effectiveness = (ElementalTypes[(int)move.type]
                              .effectivness[defender->monsterType.types[0]] *
                          ElementalTypes[(int)move.type]
                              .effectivness[defender->monsterType.types[1]]);
  return effectiveness;
}

void execute_attack(AttackMonster *attacker, AttackMonster *defender,
                    const Move *move) {
  //printf("%s\n", KBLU);
  printf("\n%s used %s!\n", attacker->monsterType.name, move->name);
  printf("MOVE INFO: POWER: %d, TYPE: %s, CONDITION: %s", move->power, ElementalTypes[(int)move->type].name, statusConditions[move->statusCondition].name);
  // printf("ATTACKER INFO: ");
  // printf("DEFENCE INFO: ");  
  
  printf("\nATTACKER CHANGES:\n");
  // Apply attacker stat changes
  if (move->attackerAtk != 0) {
    apply_stat_change(attacker, ATK, move->attackerAtk);
  }
  if (move->attackerDef != 0) {
    apply_stat_change(attacker, DEF, move->attackerDef);
  }
  if (move->attackerSpd != 0) {
    apply_stat_change(attacker, SPD, move->attackerSpd);
  }
  if (move->attackerHPperc != 0) {
    apply_stat_change(
        attacker, HP,
        (int)(attacker->monsterType.health * move->attackerHPperc));
  }
  if (move->clearAttackerDebuffs) {
    clear_debuffs(attacker);
  }
  printf("\nDEFENDER CHANGES:\n");
  // Apply defender stat changes
  if (move->defenderAtk != 0) {
    apply_stat_change(defender, ATK, move->defenderAtk);
  }
  if (move->defenderDef != 0) {
    apply_stat_change(defender, DEF, move->defenderDef);
  }
  if (move->defenderSpd != 0) {
    apply_stat_change(defender, SPD, move->defenderSpd);
  }
  if (move->defenderHP != 0) {
    apply_stat_change(defender, HP, move->defenderHP);
  }
  if (move->clearDefenderPositiveBuff) {
    clear_positive_buffs(defender);
  }

  // Check for status condition
  if (move->statusConditionChance > 0 && move->statusCondition != N_SC) {
    // if (roll_chance(move->statusConditionChance)) {
    apply_status_condition(defender, &statusConditions[move->statusCondition]);
  }
  //}

  
  // Calculate damage and apply it to the defender
  double effectiveness = calculate_effectiveness(defender, *move);
  int damage = (int)(move->power *
                     ((double)attacker->currentAttack /
                          (double)defender->currentDefense +
                      defender->statusDefenseModifier) *
                     effectiveness);
  
  if (damage > 0) {
    apply_stat_change(defender, HP, -damage);
}
}

void execute_cpu_move(AttackMonster *cpu_monster,
                      AttackMonster *player_monster) {
  printf("%s\n", KRED);
  execute_attack(
      cpu_monster, player_monster,
      &elementalMoves[cpu_monster->monsterType.monsterMoves[rand() % 4]]);
  if (player_monster->currentHP <= 0) {
    printf("Your %s has fainted!\n", player_monster->monsterType.name);
  }
  printf("%s\n", KWHT);
}

void execute_player_move(AttackMonster *player_monster,
                         AttackMonster *cpu_monster, int selected_move_index) {
  printf("%s\n", KBLU);
  execute_attack(player_monster, cpu_monster,
                 &elementalMoves[selected_move_index]);
  if (cpu_monster->currentHP <= 0) {
    printf("The CPU's %s has fainted!\n", cpu_monster->monsterType.name);
  }
  printf("%s\n", KWHT);
}

void run_battle(Team *player_team, Team *cpu_team) {
  // Set up the battle loop
  int player_current_monster_index = 0;
  int cpu_current_monster_index = 0;
  bool battle_over = false;
  while (!battle_over) {
    // Print out the current monster for each team
    AttackMonster *player_current_monster =
        &player_team->monstersA[player_current_monster_index];
    AttackMonster *cpu_current_monster =
        &cpu_team->monstersA[cpu_current_monster_index];
    printf("Player: \t");
    print_health_bar(player_current_monster);
    printf("CPU:    \t");
    print_health_bar(cpu_current_monster);
    printf("%s", KWHT);
    // Prompt the player to select a move
    int selected_move_index = prompt_move_selection(player_current_monster);
    // Determine the move order and execute the moves
    if (player_current_monster->currentSpeed +
            player_current_monster->statusSpeedModifier >
        cpu_current_monster->currentSpeed + cpu_current_monster->currentSpeed) {
      execute_player_move(player_current_monster, cpu_current_monster,
                          selected_move_index);
      if (cpu_current_monster->currentHP <= 0) {
        cpu_current_monster_index++;
        // Check if the battle is over and print appropriate message
        if (cpu_current_monster_index >= cpu_team->size) {
          battle_over = true;
          printf("You won the battle!\n");
        } else {
          printf(
              "The CPU sends out %s!\n",
              cpu_team->monstersA[cpu_current_monster_index].monsterType.name);
        }
      } else {
        execute_cpu_move(cpu_current_monster, player_current_monster);
        if (player_current_monster->currentHP <= 0) {
          player_current_monster_index++;
          if (player_current_monster_index >= player_team->size) {
            battle_over = true;
            printf("You lost the battle!\n");
          } else {
            printf("Go, %s!\n",
                   player_team->monstersA[player_current_monster_index]
                       .monsterType.name);
          }
        }
      }
    } else {
      execute_cpu_move(cpu_current_monster, player_current_monster);
      if (player_current_monster->currentHP <= 0) {
        player_current_monster_index++;
        if (player_current_monster_index >= player_team->size) {
          battle_over = true;
          printf("You lost the battle!\n");
        } else {
          printf("Go, %s!\n",
                 player_team->monsters[player_current_monster_index]
                     .monsterType.name);
        }
      } else {
        execute_player_move(player_current_monster, cpu_current_monster,
                            selected_move_index);
        if (cpu_current_monster->currentHP <= 0) {
          cpu_current_monster_index++;
          if (cpu_current_monster_index >= cpu_team->size) {
            battle_over = true;
            printf("You won the battle!\n");
          } else {
            // printf("The CPU's %s has fainted!\n",
            // cpu_current_monster->monsterType.name);
            printf("The CPU sends out %s!\n",
                   cpu_team->monstersA[cpu_current_monster_index]
                       .monsterType.name);
          }
        }
      }
    }
  }
  return;
}

