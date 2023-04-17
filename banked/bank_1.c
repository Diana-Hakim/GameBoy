#include <stdio.h>
#include <gb/gb.h>
#include <gb/console.h>

#include "Data/Background/splashscreen_data.h"
#include "Data/Background/splashscreen_map.h"
#include "Data/constants.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// BANK 1: SPLASH SCREEN ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int var_1;  /* In external RAM bank 1 */

void bank_1() NONBANKED /* In ROM bank 1 */
{
  //puts("I'm in ROM bank 1");
}


void splashPage(void) BANKED {
    // Show splash screen
    set_bkg_data(0, 136, splashscreen_data);
    set_bkg_tiles(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, splashscreen_map);
  
    SHOW_BKG;
    DISPLAY_ON;
  
    // Wait until "Start" is pressed
    waitpad(J_START);

    // Set the background tile at position (0, 0) to tile index 0
    set_bkg_tiles(0, 0, 1, 1, 256);
    printf("-----LETS PLAY---------");

}