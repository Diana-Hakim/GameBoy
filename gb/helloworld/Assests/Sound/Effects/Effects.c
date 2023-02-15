#include <gb/gb.h>

void playDoorSound() {
  NR41_REG = 0x3D;
  NR42_REG = 0xA2;
  NR43_REG = 0x09;
  NR44_REG = 0xC0;
}

void playCollisionSound(){
    NR10_REG = 0x16; 
    NR11_REG = 0x40;
    NR12_REG = 0x73;  
    NR13_REG = 0x00;   
    NR14_REG = 0xC3;	
}