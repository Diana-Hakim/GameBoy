#include <gb/gb.h>
#include <stdio.h>
#include <gb/console.h>
#include "Data/Background/selectscreen_data.h"
#include "Data/Background/selectscreen_map.h"
#include "Data/constants.h"
#include "Data/Monsters/monsters.h"
#include "Data/Cursors/Cursors.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// BANK 3: SELECT SCREEN ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int var_3;  /* In external RAM bank 3 */


UBYTE currentList = 1;
const UBYTE startCursor = 40; 


void clearScreen() {
    UINT8 i, j;
    for (i = 0; i < 18; i++) {
        for (j = 0; j < 20; j++) {
            gotoxy(j, i);
            printf("%c", 0x00);
        }
    }
    gotoxy(0, 0);
}


void setBackground(Team* team){
    clearScreen();
    // set_bkg_tiles(0,0,20,18,Select_Screen_map);
    gotoxy(0, 0);
    printf("Select Your Monsters");
    gotoxy(13, 8);
    printf("Stats:");
    gotoxy(13, 12);
    printf("HP");
    gotoxy(13, 13);
    printf("Atk");
    gotoxy(13, 14);
    printf("Sp");
    gotoxy(13, 15);
    printf("Def");
    gotoxy(3, 17);
    printf("Selected:");
    gotoxy(12, 17);
    printf("%d", getNumSelectedMonsters(team));

    
}


void displayMonsterList(int listNum) {
    int i;
    int row = 3;

    // Print out the monsters for the given list number
    for (i = (listNum - 1) * 13; i < listNum * 13; i++) {
        if (i < MAX_MONSTERS) {
            gotoxy(1, row + i % 13);
            printf("%s\n", monsters[i].name);
        }
    }
}

void setBackground(Team* team){
    clearScreen();
    // set_bkg_tiles(0,0,20,18,Select_Screen_map);
    gotoxy(0, 0);
    printf("Select Your Monsters");
    gotoxy(13, 8);
    printf("Stats:");
    gotoxy(13, 12);
    printf("HP");
    gotoxy(13, 13);
    printf("Atk");
    gotoxy(13, 14);
    printf("Sp");
    gotoxy(13, 15);
    printf("Def");
    gotoxy(3, 17);
    printf("Selected:");
    gotoxy(12, 17);
    printf("%d", getNumSelectedMonsters(team));

    
}



void selectMonsters(Team* team) {
    set_bkg_data(0, 15, Select_Screen_data); 
    set_bkg_tiles(0,0,20,18,Select_Screen_map);
    // printf("%d",(int)team->teamMembers[0]);
    // setBackground(team);
    // selectInput(team);
}

void selectInput(Team* team) {
    int i;
    int row; 
    UBYTE cursor_loc;     
    UBYTE exit_loop;
    row = 3;
    i = 0;

    cursor_loc = startCursor;

    set_sprite_data(0, 1, Cursors);
    set_sprite_tile(0, 80); // moving cursor
    move_sprite(80, 9, cursor_loc);

    // Print out the first list of monsters
    displayMonsterList(13);

    // Print out the info for the first monster
    displayMonsterInfo(&monsters[0]);

    exit_loop = 0;
    while(!exit_loop){
        switch(joypad()){
        case J_UP: 
            if (currentList == 1 && i == 0) {
                // playCollisionSound();
                performantdelay(2);
                break;  // do not move the cursor or index
            }
            if (cursor_loc > (row + 1) * 10) {  // move the cursor up if it's not at the top of the list
                cursor_loc -= 8;
                move_sprite(80, 9, cursor_loc);  // move the cursor sprite
                i--;
                if (i < 0) {
                    currentList = (currentList == 1) ? 2 : 1;
                    i = (currentList == 1) ? 12 : MAX_MONSTERS - 13;
                    setBackground(team);
                    displayMonsterList(currentList);
                    cursor_loc = (row + 1) * 10 + i * 8;
                    move_sprite(80, 9, cursor_loc);
                }
                displayMonsterInfo(&monsters[(currentList - 1) * 13 + i]);
            }
            break;
            case J_DOWN: 
                if (cursor_loc < ((row + 13) * 8) + 16) {  // move the cursor down if it's not at the bottom of the list
                    cursor_loc += 8;
                    move_sprite(80, 9, cursor_loc);  // move the cursor sprite
                    i++;
                    if (i > 13 || (currentList == 2 && i >= MAX_MONSTERS - 13)) {
                        currentList = (currentList == 1) ? 2 : 1;
                        i = 0;
                        setBackground(team);
                        displayMonsterList(currentList);
                        cursor_loc = (row + 1) * 10;
                        move_sprite(80, 9, cursor_loc);
                    }
                    displayMonsterInfo(&monsters[(currentList - 1) * 13 + i]);
                }
                break;
            case J_START:
                if (team->monsters[0].index != NO_MONSTER) { // option to have less monsters
                    exit_loop = 1;
                }
                break;
            case J_A:
                if (getNumSelectedMonsters(team) < MAX_TEAM) {
                    enum MonsterIndex selectedMonster = monsters[(currentList - 1) * 13 + i].index;
                        addMonster(team, selectedMonster);
                        gotoxy(12, 17);
                        printf("%d", getNumSelectedMonsters(team));
                } else {
                    exit_loop = 1;
                }
                break;
            case J_B:
                if (getNumSelectedMonsters(team) > 0) {
                    removeMonster(team, getNumSelectedMonsters(team) - 1);
                    gotoxy(12, 17);
                    printf("%d", getNumSelectedMonsters(team));
                }
                break;
        }
        performantdelay(10);
    }
}

void displayMonsterInfo(Monster *monster) {
    int i;
    for (i = 0; i < 2; i++) {
        gotoxy(13, 9+i);
        if (i == 1 && monster->types[0] == monster->types[1]) {
            printPaddedString(" ", 6);
        } else {
            printPaddedString(ElementalTypes[monster->types[i]].name, 6);
        }
    }
        // Print the monster's stats
    gotoxy(16, 12);
    printPaddedNumber(monster->health, 3);
    gotoxy(16, 13);
    printPaddedNumber(monster->attack, 3);
    gotoxy(16, 14);
    printPaddedNumber(monster->speed, 3);
    gotoxy(17, 15);
    printPaddedNumber(monster->defense, 2);
}


int getNumSelectedMonsters(Team* team) {
    int j;
    int count = 0;
    for (j = 0; j < 6; j++){
        if (team->monsters[j].index != NO_MONSTER) {
            count++;
        }
    }
    return count;
}







void addMonster(Team* team, enum MonsterIndex index) {
    int i;
    for (i = 0; i < MAX_TEAM; i++) {
        if (team->monsters[i].index == NO_MONSTER) {
            // create a new instance of the monster using the provided index and assign the new monster to the first available slot in the array
            team->monsters[i] =  monsters[index];
            return;
        }
    }
}



void removeMonster(Team* team, int index) {
    int i;
    for (i = index; i < 5; i++) {
        team->monsters[i] = team->monsters[i+1];
    }
    team->monsters[getNumSelectedMonsters(team)].index = (enum MonsterIndex) NO_MONSTER;
}


void bank_3() NONBANKED /* In ROM bank 3 */
{
  set_bkg_data(37, 15, Select_Screen_data); 
  set_bkg_tiles(0,0,DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, Select_Screen_map);
  SWITCH_ROM_MBC1(2);
}

