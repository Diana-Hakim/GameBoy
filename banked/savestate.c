#include <gb/gb.h>
#include "Data/Characters/characters_data.h"
// #include "bank.h"



GameCharacter player = {
    {0, 1, 2, 3}, // Sprite IDs
    0,            // Sprite index
    0,            // Spawn room number
    80,           // X coordinate
    78,           // Y coordinate
    0,            // Tile location
    DOWN,         // Facing direction
    {-1, -1, -1, -1, -1, -1} // Team
};