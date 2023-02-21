#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <gb/font.h>

void setUpEniroment();
void performantdelay(UINT8);
void clearScreen();

#define FRACTIONAL_BITS 8
#define ONE (1 << FRACTIONAL_BITS)

#include "SplashPage/SplashPage.c"
#include "Navigation/navigation.c"



int main(void){
  setUpEniroment();
  splashPage();

  SHOW_BKG;
  SHOW_SPRITES;
  setNavi();
  //setUpPlayer();
  //Navigation();
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ACTION: SET UP
/// @brief 
void setUpEniroment(){
  NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
  NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
  NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels

}
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

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}
