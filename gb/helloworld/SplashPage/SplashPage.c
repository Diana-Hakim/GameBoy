#include "SplashPage.h"

UINT8 i;

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void fadeout(UINT8 time){
	for(i=0;i<4;i++){
		switch(i){
			case 0:
				BGP_REG = 0xE4;
				break;
			case 1:
				BGP_REG = 0xF9;
				break;
			case 2:
				BGP_REG = 0xFE;
				break;
			case 3:
				BGP_REG = 0xFF;	
				break;						
		}
		performantdelay(time);
	}
}

void fadein(UINT8 time){
	for(i=0;i<3;i++){
		switch(i){
			case 0:
				BGP_REG = 0xFE;
				break;
			case 1:
				BGP_REG = 0xF9;
				break;
			case 2:
				BGP_REG = 0xE4;
				break;					
		}
		performantdelay(time);
	}
}


void splashPage(){
  // Show splash screen
  set_bkg_data(0, 136, splashscreen_data);
  set_bkg_tiles(0, 0, 20, 18, splashscreen_map);
  
  SHOW_BKG;
  DISPLAY_ON;
  
  // Wait until "Start" is pressed
  waitpad(J_START);

  fadeout(10);
  //fadein();
  
  // Clear the screen
  //cls(); 
  
  // Output message
  //puts("Let's Play");

  
  // Delay for 1 second
  //delay(1000);
  //HIDE_BKG;

}