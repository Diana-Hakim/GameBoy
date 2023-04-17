#include <gb/gb.h>
#include <stdio.h>
#include <gb/console.h>
#include <gb/font.h>


#include "bank.h" 

/// BACKGROUND
#include "Data/Background/room1_data.h"
#include "Data/Background/room2_data.h"
#include "Data/Background/room3_data.h"
#include "Data/Background/room1_map.h"
#include "Data/Background/room2_map.h"
#include "Data/Background/room3_map.h"

/// CHARACTERS, CONSTTANTS, BANK SWITCHING
#include "Data/constants.h"
#include "Data/Characters/characters_data.h"
#include "Data/Characters/characters_data_sprites.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// BANK 2: NAVIGATION ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern GameCharacter player;

int var_2;  /* In external RAM bank 2 */


const BattleCPU battleCPUs[] = {
     {"Hey there! \nAre you up for a \nbattle?","End","Jacob", {{4,5,6,7}, 1, 1, RIGHT_X, TOP_Y, 0, DOWN, {0,1,2,3,4,5} }},
     {"You will Never \nWin      \n            ","End","John", {{4,5,6,7}, 0, 2, MIDDLE_X, MIDDLE_Y, 0, DOWN, {6,7,8,9,10,11} }},
     {"Champion   \n         \n        ","End","Sarah", {{4,5,6,7}, 1, 3, MIDDLE_X, MIDDLE_Y, 0, DOWN, {12,13,14,15,16,17} }}
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////// UTILITY 

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

UINT16 convert_tile_index(UINT8 x, UINT8 y) {
    UINT16 indexTLxl = (x - 8) / 8;
    UINT16 indexTLyl = (y - 16) / 8;
    return 20 * indexTLyl + indexTLxl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////// LOAD/MOVE CHARACTERS


void assignCharacterSpriteTiles(GameCharacter* charac) {
    set_sprite_tile((int)charac->spriteID[0], (int)charac->spriteID[0]);
    set_sprite_tile((int)charac->spriteID[1], (int)charac->spriteID[1]);
    set_sprite_tile((int)charac->spriteID[2], (int)charac->spriteID[2]);
    set_sprite_tile((int)charac->spriteID[3], (int)charac->spriteID[3]);
}

void scrollCharacterSprites(GameCharacter* character, INT8 x, INT8 y) {
    scroll_sprite(character->spriteID[0], x, y);
    scroll_sprite(character->spriteID[1], x, y);
    scroll_sprite(character->spriteID[2], x, y);
    scroll_sprite(character->spriteID[3], x, y);
}


void moveCharacterSprites(GameCharacter* character) {
    move_sprite(character->spriteID[0], character->x, character->y);
    move_sprite(character->spriteID[1], character->x, character->y + BIT);
    move_sprite(character->spriteID[2], character->x + BIT, character->y);
    move_sprite(character->spriteID[3], character->x + BIT, character->y + BIT);   
}

void update_sprites(GameCharacter* character, int isMoving) {
    set_sprite_data(character->spriteID[0], 4, 
    characterSprites[character->spriteIndex][((int)character->facing_direction) + (isMoving ? 4 : 0)]);
}


direction opposite_direction(GameCharacter* character, direction facing_direction) {
    direction opposite = facing_direction + ((facing_direction % 2 == 0) ? 1 : -1);
    character->facing_direction = opposite;
    update_sprites(character, 0);
    return opposite;
}

void moveCharacter(GameCharacter* character, UINT8 x, UINT8 y) {
    update_sprites(character, 1); /// MOVING
    character->x = x;
    character->y = y;
    character->tileLocation = convert_tile_index(character->x, character->y); // UPDATE TILE 
    performantdelay(5); // WAIT
    update_sprites(character, 0); // 
    moveCharacterSprites(character); // UPDATE SPRITE BASED ON X, Y 
    
}

void scrollCharacter(GameCharacter* character, UINT8 x, UINT8 y) {
    update_sprites(character, 1); /// MOVING
    scrollCharacterSprites(character->spriteID, x, y); // UPDATE SPRITE BASED ON X, Y 
    character->x += x;
    character->y += y;
    character->tileLocation = convert_tile_index(character->x, character->y); // UPDATE TILE 
    performantdelay(5); // WAIT
    update_sprites(character, 0); // NOT MOVING
    
    
}

void loadCharacter(GameCharacter* character) {
    assignCharacterSpriteTiles(character);
    update_sprites(character, 0);
    moveCharacter(character, character->x, character->y);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////// LOAD/BACKGROUND 

void loadRoom(int index) { /// LOAD ROOM #
  switch(index) {
    case 1:
      set_bkg_data(BACKGROUND_START, 15, room1_data);
      set_bkg_tiles(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, room1_map);
      break;
    case 2:
      set_bkg_data(BACKGROUND_START, 19, room2_data);
      set_bkg_tiles(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, room2_map);
      break;
    case 3:
      set_bkg_data(BACKGROUND_START, 15, room3_data);
      set_bkg_tiles(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, room3_map);
      break;
    default:
      // Handle error case
      break;
      
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// LOAD CPU








////////////////////////////////////////////////////////////////////////////////////////////////////////////////// COLLISION




/////////////////////////////////////////////////////////////////////////////////////////////////////////////// NAVIGATION LOOP




int moveInput(){
  // BattleCPU *battleCPU;
  // SelectCPU *selectCPU;
  // char dialog[100];
    while(1){ 
        // UBYTE results = 0;
    switch(joypad()){
        case J_LEFT: 
            // if (character->facing_direction == LEFT && canPlayerMove(character->x-BIT, character->y, character->x-BIT/2, character->y)){
                scrollCharacter(&player, -BIT/2, 0);
                // moveCharacter(&character, character->x-BIT/2, character->y);
            // } else {
                // character->facing_direction = LEFT;
                // update_sprites(&character,0);
            // }
            break; 
        case J_RIGHT: 
            // if ((character->facing_direction == RIGHT) && canPlayerMove(character->x+BIT+(BIT*2),character->y, character->x+BIT/2,character->y)){
                scrollCharacter(&player, BIT/2, 0);
                // moveCharacter(&character, character->x+BIT/2, character->y);
            // } else {
                // character->facing_direction = RIGHT;
                // update_sprites(&character,0);
            // }
            break;  
        case J_UP: 
            // if (character->facing_direction == UP && canPlayerMove(character->x,character->y-BIT, character->x,character->y-(BIT/2))){
                scrollCharacter(&player, 0, -BIT/2);
                // moveCharacter(&character, character->x, character->y-BIT/2);

                // results = onDoor();
            // } else {
                // character->facing_direction = UP;
                // update_sprites(&character,0);
            // }
            break;
        case J_DOWN: 
            // if (character->facing_direction == DOWN && canPlayerMove(character->x, character->y + BIT * 3, character->x,character->y+(BIT/2))) {
            //scrollCharacter(&character, 0, BIT/2);
            scrollCharacter(&player, 0, BIT/2);
            // results = onDoor();
            // } else {
            // character->facing_direction = DOWN;
            // update_sprites(&character,0);
            // }
            break;
      case J_A:
          printf("TEXT");
    }
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// SELECT / BATTLE SCENE

/// TODO: INTERACT WITH CPUS - SELECT & BATTLE  ---- SWITCH BANKS NEEDED







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// CHANGE ROOMS

/// TODO: CHANGE ROOMS 




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// CHANGE ROOMS



// void change_room(UINT8 roomIndex){
//   loadRoom(1);
//   // loadCharacter(&battleCPUs[roomIndex].base);
//   // moveInput();
// }





void setUpNavigation(void){
  // FONTS
  font_t min_font;
  font_init();
  min_font = font_load(font_min); //36 tiles
  font_set(min_font);
  SHOW_SPRITES;
  SPRITES_8x8;
  
}


void printPlayerData() {
    printf("Sprite IDs: %u, %u, %u, %u\n", player.spriteID[0], player.spriteID[1], player.spriteID[2], player.spriteID[3]);
    printf("Sprite index: %u\n", player.spriteIndex);
    printf("Spawn room number: %u\n", player.spawnRoomNumber);
    printf("X coordinate: %u\n", player.x);
    printf("Y coordinate: %u\n", player.y);
    printf("Tile location: %u\n", player.tileLocation);
    printf("Facing direction: %u\n", player.facing_direction);
    printf("Team: %d, %d, %d, %d, %d, %d\n", player.team[0], player.team[1], player.team[2], player.team[3], player.team[4], player.team[5]);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void navigation(void) NONBANKED /* In ROM bank 2 */
{ 
  UINT8 currentRoom;
    

  setUpNavigation();
  
  currentRoom = 0;
  // change_room(currentRoom);
  loadRoom(1);

  printPlayerData();
  loadCharacter(&battleCPUs[currentRoom].base);
  //loadCharacter(&player);
  moveInput();
  

//   while(1) { // Loop indefinitely
//   if(joypad() & J_SELECT) { //// SELECT SCREEN
//     SWITCH_ROM_MBC1(2);
//     //move_sprites_to_positions(0,200,200);
//     SWITCH_ROM_MBC1(3);
//     bank_3();   
//   }

//   if(joypad() & J_START) { //// BATTLE
//     SWITCH_ROM_MBC1(2);
//     //move_sprites_to_positions(0,200,200);
//     SWITCH_ROM_MBC1(4);
//     bank_4();
//   }
//     if(joypad() & J_UP) { //// NAVIGATION
//       SWITCH_ROM_MBC1(2);
//       loadRoom(2);
//       init_sprites(0, player.x, player.y);
//       // move_sprites_to_positions(0, 100, 100);
//       // printf("WE ARE BAxCK    \n");
//   }
//   gotoxy(0,0);
  
// }
  // set_sprite_data(0,8,playerGirlTLE0);
  // set_sprite_tile(0,0);
  // set_sprite_tile(1,1);
  // set_sprite_tile(2,2);
  // set_sprite_tile(3,3);
  // move_sprite(0, 20,20);


  // //SELECT
  // SWITCH_ROM_MBC1(3);
  // bank_3();
  //   // BATTLE
  // SWITCH_ROM_MBC1(4);
  // bank_4();
  // SWITCH_ROM_MBC1(2);


}


















// #include "navigation.h"

// void* cpu;

// UINT8 roomType = 0; // Type of Room
// UINT8 currentRoom = 0; // Current Room -- CPU Index

// void startNavigation(){ // First Room
//     SPRITES_8x8;
//     cpu = (void *) &selectCPU1;
    
//     //fadeout(10);
//     displayRoom();
//     load_character(&player.base);
//     load_character(&selectCPU1.base);
//     SHOW_BKG;
//     DISPLAY_ON;
//     Navigation();
    
// }

// void NavgateCurrentRoom(){
  
//   //changeCPU(); // CHANGE CPU SPRITE and Location
//   displayRoom();
//   displayCPU();
//   //move_character(&player, player.base.x, player.base.y);
// //   fadein(5);
//   moveInput();
// }


// void Navigation(){
//   UINT8 Y_Location;

//   while (1) {
//     NavgateCurrentRoom(); //navigate current room (TYPES - 0-2 and index)
//     switch (roomType) {
//       case 0:
//         cpu = (void *) &battleCPU1;
//         Y_Location = BOTTOM_Y;
//         roomType = 1; // player left room so these values are updated
//         currentRoom = 1;
//         break;
//       case 1:
//         Y_Location = (player.base.tileLocation > 80 ? TOP_Y : BOTTOM_Y); /// IF PLAYER IS CLOSER TO TOP THEN MAP_BOTTOM ELSE MAP_TOP
//         //Y_Location = TOP_Y;
//         currentRoom += 1; // currentRoom += Y_Location == BOTTOM_Y ? 1 : -1;/// MAP_BOTTOM THEN +1 ELSE -1
//         roomType = (currentRoom == MAX_CPU-1) ? (roomType + 1) : ((currentRoom == 0) ? (roomType - 1) : roomType); //
//         cpu = (currentRoom == 2) ? (void *) &battleCPU2 : (void *) &battleCPU3;
//         break;
//       case 2: // going back
//         cpu = (void *) &selectCPU1;
//         Y_Location = TOP_Y;       
//         roomType--;
//         currentRoom--; 
//         break;
//     }
//     moveCharacter(&player.base, MIDDLE_X, Y_Location);
//     performantdelay(5);
//   }
// }




// void moveInput(){
//   BattleCPU *battleCPU;
//   SelectCPU *selectCPU;
//   char dialog[100];
//     while(1){ 
//         UBYTE results = 0;
//     switch(joypad()){
//         case J_LEFT: 
//             if (player.base.facing_direction == LEFT && canPlayerMove(player.base.x-BIT, player.base.y, player.base.x-BIT/2, player.base.y)){
//                 scrollCharacter(&player.base, -BIT/2, 0);
//             } else {
//                 player.base.facing_direction = LEFT;
//                 update_sprites(&player.base,0);
//             }
//             break; 
//         case J_RIGHT: 
//             if ((player.base.facing_direction == RIGHT) && canPlayerMove(player.base.x+BIT+(BIT*2),player.base.y, player.base.x+BIT/2,player.base.y)){
//                 scrollCharacter(&player.base, BIT/2, 0);
//             } else {
//                 player.base.facing_direction = RIGHT;
//                 update_sprites(&player.base,0);
//             }
//             break;  
//         case J_UP: 
//             if (player.base.facing_direction == UP && canPlayerMove(player.base.x,player.base.y-BIT, player.base.x,player.base.y-(BIT/2))){
//                 scrollCharacter(&player.base, 0, -BIT/2);
//                 results = onDoor();
//             } else {
//                 player.base.facing_direction = UP;
//                 update_sprites(&player.base,0);
//             }
//             break;
//         case J_DOWN: 
//             if (player.base.facing_direction == DOWN && canPlayerMove(player.base.x, player.base.y + BIT * 3, player.base.x,player.base.y+(BIT/2))) {
//             scrollCharacter(&player.base, 0, BIT/2);
//             results = onDoor();
//             } else {
//                 player.base.facing_direction = DOWN;
//                 update_sprites(&player.base,0);
//             }
//             break;
//         case J_A:
//             if (isLookingAtCPU()){
//                   if (cpu_is_battle(cpu)) {
//                       battleCPU = (BattleCPU *) cpu;
//                       opposite_direction(&battleCPU->base, player.base.facing_direction);
//                       sprintf(dialog, "%s: %s", battleCPU->name, battleCPU->initDialog);
//                       ////TODO: BATTLE
//                   } else {
//                       selectCPU = (SelectCPU *) cpu;
//                       opposite_direction(&selectCPU->base, player.base.facing_direction);
//                       sprintf(dialog, "%s: %s", selectCPU->name, selectCPU->initDialog);
//                       ////TODO: SELECT
//                   }
//                   printDialog(dialog);
//             }
//             break;
//     }
//         if (results){
//           break;
//         }
//     }
// }



// void printDialog(const char *message) {
//     UINT8 x, y, i, lineCount;
//     char line[21];

//     // Print a white box on the screen as background for the dialog
//     for (y = 0; y < 5; y++) {
//         for (x = 0; x < 20; x++) {
//             gotoxy(x, y+10);
//             printf(" ");
//         }
//     }

//     // Print the dialog message on top of the background box
//     lineCount = 0;
//     while (*message != '\0') {
//         for (i = 0; i < 20 && *message != '\0' && *message != '\n'; i++, message++) {
//             line[i] = *message;
//         }
//         if (*message == '\n') {
//             message++; // Skip the newline character
//         }
//         line[i] = '\0';
//         gotoxy(0, 11+lineCount);
//         printf("%s", line);
//         performantdelay(60);
//         while(joypad() & J_A) {}
//         lineCount++;
//     }
    
//     // Clear any remaining lines
//     for (y = 11+lineCount; y < 14; y++) {
//         for (x = 0; x < 20; x++) {
//             gotoxy(x, y);
//             printf(" ");
//         }
//     }
//     wait_vbl_done();
//     while(joypad() & J_A) {}
    
//     //set_bkg_data(0,rooms[roomType].numberOfTiles, rooms[roomType].roomdata); 
//     set_bkg_tiles(0,0,20,18,rooms[roomType].roommap);
// }


// void displayRoom(){
//   set_bkg_data(0,rooms[roomType].numberOfTiles, rooms[roomType].roomdata); 
//   set_bkg_tiles(0,0,20,18,rooms[roomType].roommap);
// }



// int cpu_is_battle(void *cpu) {
//     // Cast the CPU pointer to a BattleCPU pointer
//     BattleCPU *battleCPU;
//      battleCPU = (BattleCPU *) cpu;

//     // Check if the isBattleCPU field is set to true (non-zero)
//     return battleCPU->isBattleCPU;
// }





// UBYTE onDoor() {
//     UINT8 tileIndex;
//     switch (player.base.facing_direction) {
//         case DOWN:
//             tileIndex = convert_tile_index(player.base.x + (BIT/2), player.base.y + (BIT*2));
//             return (rooms[roomType].roommap[tileIndex] == rooms[roomType].doors[0] || rooms[roomType].roommap[tileIndex] == rooms[roomType].doors[1]);
//         case UP:
//             tileIndex = convert_tile_index(player.base.x + (BIT/2), player.base.y - BIT);
//             return (rooms[roomType].roommap[tileIndex] == rooms[roomType].doors[0] || rooms[roomType].roommap[tileIndex] == rooms[roomType].doors[1]);
//         default:
//             return 0; // Default to not on door if the facing direction is not recognized
//     }
// }

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// // Checks if there is a wall collision at the given coordinates
// UBYTE isWallCollisionDetected(UINT8 newplayerx, UINT8 newplayery) {
//     return (rooms[roomType].roommap[convert_tile_index(newplayerx, newplayery)] == WALL);
// }

// // Checks if there is a CPU collision at the given coordinates
// UBYTE isCPUCollisionDetected(UINT8 newplayerx, UINT8 newplayery) {
//     UINT8 cpuX, cpuY;

//     if (cpu == NULL) {
//         return 0;
//     }
    
//     if (((SelectCPU*)cpu)->isBattleCPU) {
//         BattleCPU* battleCPU = (BattleCPU*)cpu;
//         cpuX = battleCPU->base.x;
//         cpuY = battleCPU->base.y;
//     } else {
//         SelectCPU* selectCPU = (SelectCPU*)cpu;
//         cpuX = selectCPU->base.x;
//         cpuY = selectCPU->base.y;
//     }

//     return (newplayerx + BIT >= cpuX) && 
//            (newplayerx <= cpuX + BIT) && 
//            (newplayery + BIT + (BIT / 2) >= cpuY) && 
//            (newplayery <= cpuY + BIT);
// }

// // Checks if the player is looking at the CPU
// UBYTE isLookingAtCPU() {
//     UINT8 player_x = player.base.x;
//     UINT8 player_y = player.base.y;

//     switch (player.base.facing_direction) {
//         case UP:
//             player_y -= BIT/2;
//             break;
//         case DOWN:
//             player_y += BIT/2;
//             break;
//         case LEFT:
//             player_x -= BIT/2;
//             break;
//         case RIGHT:
//             player_x += BIT/2;
//             break;
//     }

//     return isCPUCollisionDetected(player_x, player_y);
// }




// UBYTE canPlayerMove(UINT8 newPlayerX1, UINT8 newPlayerY1, UINT8 newPlayerX2, UINT8 newPlayerY2)
// {
//     UBYTE result = 1; // Assume the player can move by default

//     // Check for collision with walls or other objects
//     if (isWallCollisionDetected(newPlayerX1, newPlayerY1) || isCPUCollisionDetected(newPlayerX2, newPlayerY2))
//     {
//         result = 0; // Player cannot move
//         //playCollisionSound();
//     }

//     return result;
// }


// void displayCPU() {
//   GameCharacter *character = NULL;
//   SelectCPU *selectCPU = NULL;
//   BattleCPU *battleCPU = NULL;
  
//   if (cpu != NULL) {
//     if (((SelectCPU *)cpu)->isBattleCPU) {
//       battleCPU = (BattleCPU *) cpu;
//       character = &(battleCPU->base);
//     } else {
//       selectCPU = (SelectCPU *) cpu;
//       character = &(selectCPU->base);
//     }
//   }
  
//   if (character != NULL) {
//     update_sprites(character, 0);
//     assignCharacterSpriteTiles(character);
//     moveCharacter(character, character->x, character->y);
//   }
  
// }