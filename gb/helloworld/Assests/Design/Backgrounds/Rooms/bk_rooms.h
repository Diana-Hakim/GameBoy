#include <gb/gb.h>

#ifndef BK_ROOM_H
#define BK_ROOM_H

#define MAX_ROOMS 3



typedef struct Room {
  const unsigned char *roomdata;
  const unsigned char *roommap;
  UINT8 numberOfTiles;
  unsigned char doors[2];
} Room;

const unsigned char wall[1] = {0x00};

extern const Room rooms[MAX_ROOMS];

#endif