
#include "monsterSelect.h"
#include "../Assests/Design/Background/Select/Select_Screen_data.c"
#include "../Assests/Design/Background/Select/Select_Screen_map.c"
#include "../Assests/Design/Sprite/Cursors.c"
#include <gb/console.h>



//#define selected_options_count 6

// UBYTE selectInput(){
//     UBYTE selectedMonsters = 0;
//     while(selectedMonsters > 0){ 

//         switch(joypad()){
//             case J_LEFT: 
//                 break;
//             case J_RIGHT: 
//                 break;  
//             case J_UP: 
//                 break; 
//             case J_DOWN: 
//                 break;
//             case J_A:
//                 break;
//             case J_B:
//                 break;
//         performantdelay(6); 
        
//     }





void selectMonsters() {
    // MOVE SPRITES OFF SCREEN
    int i;
    //xxfas
    int row = 3; 
    int cursor_loc;
    SHOW_SPRITES;
    set_bkg_data(0,64, Select_Screen_data); 
    set_bkg_tiles(0,0,20,18,Select_Screen_map);
    //set_sprite_data(17, 17, Cursors); 
    // set_sprite_tile(17,17);
    // move_sprite(17, 9, 5*8);
    set_sprite_data(0, 1, Cursors); 
    set_sprite_tile(17,0);
    move_sprite(17, 20, 30);


    cursor_loc = (row+1)*10; 


    for (i = 0; i < MAX_MONSTERS-10; i++) {
        set_sprite_data(18+i, 8, Cursors); 
        set_sprite_tile(18+i,0);
        
        move_sprite(18+i, 9, cursor_loc);
        cursor_loc+=8;
        gotoxy(1, row);
        printf("%s\n", monsters[i].name);
        row++;
    }




    waitpad(J_START);
    }
