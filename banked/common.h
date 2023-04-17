#ifndef COMMON_H   // Include guards to prevent multiple inclusion
#define COMMON_H

#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <gb/console.h>

void clearScreen();
void performantdelay(UINT8 numloops);
void printPaddedNumber(int num, int length);
void printPaddedString(char* str, int length);
void fadeout(UINT8 time);
void fadein(UINT8 time);



// UINT16 convert_tile_index(UINT8 x, UINT8 y) {
//     UINT16 indexTLxl = (x - 8) / 8;
//     UINT16 indexTLyl = (y - 16) / 8;
//     return 20 * indexTLyl + indexTLxl;
// }

#endif