#ifndef NAVIGATION_H
#define NAVIGATION_H


#include "../Assests/Sound/Effects/Effects.c"
#include "../Assests/Design/Sprites/Character/Player/SmilerSprites.c"
#include "../Assests/Design/Sprites/Character/Player/Female/Female_Player.c"
#include "../Assests/Design/Backgrounds/Rooms/bk_rooms.c"
#include "../MonsterInfo/monsters.h"
#include "../CharacterInfo/GameCharacter.c"
#include "../MonsterSelect/monsterSelect.c"


// Function prototypes
int setNavi();
UBYTE moveInput();
UBYTE canplayermove(UINT8 newplayerx1, UINT8 newplayery1, UINT8 newplayerx2, UINT8 newplayery2);
UINT16 convertTileIndex(UINT8 newplayerx, UINT8 newplayery);
void Navigation();
UBYTE onDoor(UINT8 Py);
void NavgateCurrentRoom();
void setUpPlayer();
void changeCPU();
void updategamecharacter(struct GameCharacter* character);
void movegamecharacter(struct GameCharacter* character, UINT8 x, UINT8 y);
UBYTE isCPUCollisionDetected(UINT8 newplayerx, UINT8 newplayery);
UBYTE isLookingAtCPU();

#endif // NAVIGATION_H