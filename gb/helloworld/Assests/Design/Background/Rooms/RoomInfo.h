#include <gb/gb.h>

#include "Room_Middle/room_middle_data.c"
#include "Room_Bottom/room_bottom_data.c"
#include "Room_Top/room_top_data.c"

#include "Room_Middle/room_middle_map.c"
#include "Room_Bottom/room_bottom_map.c"
#include "Room_Top/room_top_map.c"


#define MAX_ROOMS 3

const unsigned char wall[1] = {0x00};

typedef struct Room {
  const unsigned char *roomdata;
  const unsigned char *roommap;
  UINT8 numberOfTiles;
  unsigned char doors[2];
} Room;

const Room rooms[MAX_ROOMS] = {
  {room_top_data, room_top_map, 15, {0x04, 0x03}},
  {room_middle_data, room_middle_map, 19, {0x04, 0x11}},
  {room_bottom_data, room_bottom_map, 15, {0x0C, NULL}}
};

