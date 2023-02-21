#include "navigation.h"
#include <gb/gb.h>
#include <stdio.h>


#define FRACTIONAL_BITS 8
#define ONE (1 << FRACTIONAL_BITS) /// FOR PRINTING

#define movementSkip 4
#define spritesize 8


struct Player player;
struct BaseCPU cpu;

UINT8 roomType = 0; // Type of Room
UINT8 currentRoom = 0; // Current Room -- CPU Index



int setNavi(){
  setUpPlayer();
  Navigation();
  return 0;
}


void setUpPlayer() {
  set_sprite_data(0, 8, Female_Player); 
  player.base.x = MIDDLE_X;
  player.base.y = MIDDLE_Y;
  player.base.facing_direction = DOWN;

  set_sprite_tile(0,0);
  player.base.spritids[0] = 0;
  set_sprite_tile(1,1);
  player.base.spritids[1] = 1;
  set_sprite_tile(2,2);
  player.base.spritids[2] = 2;
  set_sprite_tile(3,3);
  player.base.spritids[3] = 3;
}

void displayRoom(){
  set_bkg_data(0,rooms[roomType].numberOfTiles, rooms[roomType].roomdata); 
  set_bkg_tiles(0,0,20,18,rooms[roomType].roommap);
}

void NavgateCurrentRoom(){
  changeCPU(); // CHANGE CPU SPRITE and Location
  displayRoom();
  movegamecharacter(&player, player.base.x,player.base.y);
  fadein(5);
  moveInput();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////ACTION: USER INPUT

UBYTE moveInput(){
    while(1){ 
      UBYTE results = 0;
      //UINT8 modif;
        switch(joypad()){
            case J_LEFT: 
              if (player.base.facing_direction == LEFT && canplayermove(player.base.x-movementSkip*2,player.base.y, player.base.x-movementSkip,player.base.y)) { // CHECK FOR WALLS, CPUS, OR DOORS
                  movegamecharacter(&player.base, player.base.x-movementSkip,player.base.y);
              }
              /// TODO:  SPRITE DIRECTIONAL CHANGE
              player.base.facing_direction = LEFT;
                break;
            case J_RIGHT: 
              if ((player.base.facing_direction == RIGHT) && canplayermove(player.base.x+movementSkip*2+(spritesize*2),player.base.y, player.base.x+movementSkip,player.base.y)) {
                movegamecharacter(&player.base, player.base.x+movementSkip,player.base.y);
              }
              /// TODO:  SPRITE DIRECTIONAL CHANGE
                player.base.facing_direction = RIGHT;
                break;  
            case J_UP: 
                if ((player.base.facing_direction == UP) && canplayermove(player.base.x,player.base.y-movementSkip*2, player.base.x,player.base.y-movementSkip)) { 
                  movegamecharacter(&player.base, player.base.x,player.base.y-movementSkip);
                  } 
                  results = onDoor(player.base.y-movementSkip);
                  /// TODO:  SPRITE DIRECTIONAL CHANGE
                player.base.facing_direction = UP;
                break; 
            case J_DOWN: 
                if ((player.base.facing_direction == DOWN) && canplayermove(player.base.x,player.base.y+movementSkip, player.base.x,player.base.y+movementSkip)) { 
                  movegamecharacter(&player.base, player.base.x,player.base.y+movementSkip);
                  }
                  results = onDoor(player.base.y+movementSkip);
                  player.base.facing_direction = DOWN;
                  /// TODO:  SPRITE DIRECTIONAL CHANGE
                break;
            case J_A:
            if (isLookingAtCPU()){
                printf("Hello, I'M CPU: %d\n", currentRoom - ((currentRoom / ONE) * ONE));
                printf(cpu.dialog);
                waitpad(J_A);
                HIDE_SPRITES;
                if (!cpu.isBattleCPU){
                  movegamecharacter(&cpu.base, OFF_SCREEN_XY,OFF_SCREEN_XY);
                  movegamecharacter(&player.base, OFF_SCREEN_XY,OFF_SCREEN_XY);
                  selectMonsters();
                  setNavi();
                  // displayRoom();
                  // setUpPlayer();

                  // changeCPU();
                  movegamecharacter(&cpu.base, CPU_info.characters[currentRoom].base.x, CPU_info.characters[currentRoom].base.y);
                  
                  //SHOW_SPRITES;
                  
                } else {
int i;
// struct BattleCPU* battle_cpu = (struct BattleCPU*)(&cpu); // Cast `CPU` to `BattleCPU`.
// struct BattleCPU* battle_cpu = (struct BattleCPU*)(&CPU_info.characters[currentRoom]);
enum MonsterIndex* team = getCPUMonsterTeam(currentRoom);
for (i = 0; i < 6; i++) {
    enum MonsterIndex monster_index = team[i];
    printf("\nMonster %d: %s\n", i+1, monsters[monster_index].name);
}
                }
            }
              break;  
        }
        
        if (results){
          break;
        }
        performantdelay(6); 
        
    }
}

///////////////////////////////////////////////////////////////ACTION: DO CPU'S BATTLE / SELECT SEQ






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////IF: CHANGE ROOMS -- ON DOOR?

UBYTE onDoor(UINT8 Py){
    UINT16 tile = convertTileIndex(player.base.x, Py);
    UINT16 tile2 = convertTileIndex(player.base.x+(spritesize*2), Py);

    UBYTE result = (
      (rooms[roomType].roommap[tile]     == rooms[roomType].doors[0]) 
      ||(rooms[roomType].roommap[tile]   == rooms[roomType].doors[1]) 
      || (rooms[roomType].roommap[tile2] == rooms[roomType].doors[0]) 
      ||(rooms[roomType].roommap[tile2]  == rooms[roomType].doors[1]) 
      );

    if (result){
    playDoorSound();
    delay(300); // delay for the sound to play
      } 
      

  return (result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ACTION: TO CHANGE ROOMS --

void Navigation(){
  UINT8 Y_Location;
  while (1) {
    NavgateCurrentRoom(); //navigate current room (TYPES - 0-2 and index)
    switch (roomType) {
      case 0:
        Y_Location = MAP_BOTTOM;
        roomType = 1; // player left room so these values are updated
        currentRoom = 1;
        break;
      case 1:
        Y_Location = (player.base.tileLocation > 80 ? MAP_TOP : MAP_BOTTOM); /// IF PLAYER IS CLOSER TO TOP THEN MAP_BOTTOM ELSE MAP_TOP
        currentRoom += Y_Location == MAP_BOTTOM ? 1 : -1; /// MAP_BOTTOM THEN +1 ELSE -1
        roomType = (currentRoom == MAX_CPU-1) ? (roomType + 1) : ((currentRoom == 0) ? (roomType - 1) : roomType); //
        break;
      case 2: 
        Y_Location = MAP_TOP;       
        roomType--;
        currentRoom--; 
        break;
    }
    movegamecharacter(&player.base, MIDDLE_X, Y_Location);
    performantdelay(5);
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// IF: SPRITE SHOULD BE MOVED -- COLLISION

UBYTE isWallCollisionDetected(UINT8 newplayerx, UINT8 newplayery){
    if (rooms[roomType].roommap[convertTileIndex(newplayerx, newplayery)] == wall[0]){
      return 1;
    }
    return 0;
}
UBYTE canplayermove(UINT8 newplayerx1, UINT8 newplayery1, UINT8 newplayerx2, UINT8 newplayery2){ 
    UBYTE result;
    result = !(isWallCollisionDetected(newplayerx1, newplayery1) || isCPUCollisionDetected(newplayerx2, newplayery2));

    if (!result){
      playCollisionSound();
    }

    return result;
}

UBYTE isCPUCollisionDetected(UINT8 newplayerx, UINT8 newplayery) {
      return (newplayerx <= cpu.base.x + (spritesize)) && 
             (newplayerx + (spritesize) >= cpu.base.x) && 
             (newplayery<= cpu.base.y + (spritesize)) && 
             (newplayery + (spritesize) >= cpu.base.y);
}

UBYTE isLookingAtCPU() {
    UINT8 player_x = player.base.x;
    UINT8 player_y = player.base.y;
    switch (player.base.facing_direction) {
        case UP:
            player_y -= movementSkip;
            break;
        case DOWN:
            player_y += movementSkip;
            break;
        case LEFT:
            player_x -= movementSkip;
            break;
        case RIGHT:
            player_x += movementSkip;
            break;
    }
    return isCPUCollisionDetected(player_x, player_y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ACTION: TO MOVE SPRITE -- X, Y


void movegamecharacter(struct GameCharacter* character, UINT8 charx, UINT8 chary){
    character->x = charx;
    character->y = chary;
    player.base.tileLocation = convertTileIndex(player.base.x, player.base.y);
    updategamecharacter(character);
}

void updategamecharacter(struct GameCharacter* character){
    move_sprite(character->spritids[0], character->x, character->y);
    move_sprite(character->spritids[1], character->x + spritesize, character->y);
    move_sprite(character->spritids[2], character->x, character->y + spritesize);
    move_sprite(character->spritids[3], character->x + spritesize, character->y + spritesize);
}

void copyCPU(struct CPU *dest, struct CPU *src) {

    memcpy(dest, src, sizeof(struct CPU));

}

void changeCPU(){  

    copyCPU(&cpu, &CPU_info.characters[currentRoom]);

    cpu.base.tileLocation = convertTileIndex(cpu.base.x, cpu.base.y);

  // "CHANGE CHARACTER" NOT REALLY JUST THE SPITE LOOK
    set_sprite_tile(4, 4);
    cpu.base.spritids[0] = 4;
    set_sprite_tile(5, 5);
    cpu.base.spritids[1] = 5;
    set_sprite_tile(6, 6);
    cpu.base.spritids[2] = 6;
    set_sprite_tile(7, 7);
    cpu.base.spritids[3] = 7;

    updategamecharacter(&cpu.base);
}


UINT16 convertTileIndex(UINT8 newplayerx, UINT8 newplayery) {
    UINT16 indexTLxl = (newplayerx - 8) / 8;
    UINT16 indexTLyl = (newplayery - 16) / 8;
    return 20 * indexTLyl + indexTLxl;
}

