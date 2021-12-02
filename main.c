#include <gb/gb.h>
#include <stdio.h>
#include "sqgame3_data.c"
#include "sqgame3_map.c"
#include "fundo.c"
#include "background.c"

UINT8 i;

void performantdelay(UINT8 numloops){
    UINT8 ii;
    for(ii = 0; ii < numloops; ii++){
        wait_vbl_done();
    }     
}

void fadeout(){
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
		performantdelay(10);
	}
}

void fadein(){
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
		performantdelay(10);
	}
}



void main(){
    set_bkg_data(0, 114, sqgame3_data);
    set_bkg_tiles(0, 0, 20, 18, sqgame3_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);
    fadeout();

    set_bkg_data(0, 4, BackgroundTiles);
    set_bkg_tiles(0, 0, 20, 18, background);  	

	fadein();
}