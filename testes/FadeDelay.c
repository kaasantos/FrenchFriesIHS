#include<gb/gb.h>

UINT8 f;

void performantdelay(UINT8 numloops){
    UINT8 j;
    for(j = 0; j < numloops; j++){
        wait_vbl_done();
    }     
}

void fadeout(){
	for(f=0;f<4;f++){
		switch(f){
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
	for(f=0;f<3;f++){
		switch(f){
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