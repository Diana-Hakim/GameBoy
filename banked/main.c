
#include <gb/gb.h>
#include <stdio.h>


int var_internal;  /* In internal RAM */
extern int var_0;  /* In external RAM bank 0 */
extern int var_1;  /* In external RAM bank 1 */
extern int var_2;  /* In external RAM bank 2 */
extern int var_3;  /* In external RAM bank 3 */
extern int var_4;  /* In external RAM bank 3 */
extern int var_5;  /* In external RAM bank 3 */


// void bank_1() NONBANKED;
extern void splashPage(void) BANKED; // Declare the splashPage() function
extern void navigation(void) NONBANKED; // Navigation


void setUpEniroment(){ //  SOUND ON
  NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
  NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
  NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
}


void main(void)
{
  
  printf("");
  setUpEniroment();
  

  ENABLE_RAM_MBC1;
  // BANK 1: Load Splash Page
  SWITCH_ROM_MBC1(1);
  splashPage();
  // BANK 2: Load Navigation
  SWITCH_ROM_MBC1(2);
  navigation();
  SWITCH_RAM_MBC1(1);

  puts("The End....\nClose Application");

}
