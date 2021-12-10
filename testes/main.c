#include <gb/gb.h>
#include <stdio.h>
//#include "sqgame3_data.c"
//#include "sqgame3_map.c"//tela inicio
#include "GameCharacter.c" //Criação das structs
#include "characters.c" //Sprites e frames dos personagens
#include "background.c" //Sprites do mapa
#include "mapbackground.c" //Geração do mapa com os sprites definidos no background
#include "score.c"

struct GameCharacter principalatras;
struct GameCharacter principaldireita;
struct GameCharacter principalfrente;
struct Boneca bonecafixa; 
struct GameCharacter botfrente;
struct GameCharacter botatras;
struct GameCharacter botdireita;
struct ScorePoint timer;

UBYTE spritesize = 8;
<<<<<<< HEAD
UINT8 x = 76;
UINT8 y = 135;
=======
UINT8 x = 70;
UINT8 f;
UINT8 y = 140;
>>>>>>> 2185c8e449ed1a7e00651c4973541e9a9e13fbb1

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

void movegamecharacter(struct GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spritesize, y);
    move_sprite(character->spritids[2], x, y + spritesize);
    move_sprite(character->spritids[3], x + spritesize, y + spritesize);
}

void movegamecharacterboneca(struct Boneca* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spritesize, y);
    move_sprite(character->spritids[2], x, y + spritesize);
    move_sprite(character->spritids[3], x + spritesize, y + spritesize);
    move_sprite(character->spritids[4], x, y + (spritesize + spritesize));
    move_sprite(character->spritids[5], x + spritesize, y + (spritesize + spritesize));
}

void setupatras(){
    INT8 z;
    principalatras.comprimento = 16;
    principalatras.largura = 16;

    for(z = 0 ; z < 4; z++) {
        set_sprite_tile(z,z);
        principalatras.spritids[z] = z;
    }
    movegamecharacter(&principalatras, x, y);
}

void setupfrente(){
    INT8 z, w = 0;
    principalfrente.comprimento = 16;
    principalfrente.largura = 16;

    for(z = 4; z < 8; z++) {
        set_sprite_tile(z,z);
        principalfrente.spritids[w] = z;
        w++;
    }
}

void setupdireita(){
    INT8 z, w = 0;
    principaldireita.comprimento = 16;
    principaldireita.largura = 16;

    for(z = 8; z < 12; z++) {
        set_sprite_tile(z,z);
        principaldireita.spritids[w] = z;
        w++;
    }
}

void setupbotfrente(){
    INT8 z, w = 0;
    botfrente.comprimento = 16;
    botfrente.largura = 16;

    for(z = 12; z < 16; z++) {
        set_sprite_tile(z,z);
        botfrente.spritids[w] = z;
        w++;
    }
}

void setupbotatras(){
    INT8 z, w = 0;
    botatras.comprimento = 16;
    botatras.largura = 16;

    for(z = 16; z < 20; z++) {
        set_sprite_tile(z,z);
        botatras.spritids[w] = z;
        w++;
    }
    
    movegamecharacter(&botatras, 100, 140);
}

void setupbotdireita(){
    INT8 z, w = 0;
    botdireita.comprimento = 16;
    botdireita.largura = 16;

    for(z = 20; z < 24; z++) {
        set_sprite_tile(z,z);
        botdireita.spritids[w] = z;
        w++;
    }
}

void setupbonecafixa(){
    INT8 z, w = 0;
    bonecafixa.comprimento = 16;
    bonecafixa.largura = 24;

    for(z = 24; z < 30; z++) {
        set_sprite_tile(z,z);
        bonecafixa.spritids[w] = z;
        w++;
    }
    movegamecharacterboneca(&bonecafixa, 10, 130);
} 

void setups(){
    setupfrente();
    setupatras();
    setupdireita();
    setupbonecafixa();
    setupbotatras();
    setupbotfrente();
    setupbotdireita();
}

void main(){
    INT8 mapx = 44;
    INT8 mapy = 112;
    INT8 i;

    set_bkg_data(0, 114, sqgame3_data);
    set_bkg_tiles(0, 0, 20, 18, sqgame3_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);
    fadeout();

    set_bkg_data(0, 34, TileLabel);
    set_bkg_tiles(0, 0, 32, 32, mapbackground);  	
    scroll_bkg(mapx,mapy);

	fadein();

    set_sprite_data(0, 46, characters);
    set_sprite_data(46, 17, score);
    setups();
     
    SHOW_SPRITES;

    while(1){

        if(joypad() & J_LEFT){
            if(x > 28 ){
                x -= 1;
                principaldireita.spritids[1] = 8;
                principaldireita.spritids[0] = 9;
                principaldireita.spritids[3] = 10;
                principaldireita.spritids[2] = 11;

                for(i = 0; i < 4; i++) set_sprite_prop(principaldireita.spritids[i], S_FLIPX);
                
                movegamecharacter(&principalatras, -10, -10);
                movegamecharacter(&principalfrente, -10, -10);
                movegamecharacter(&principaldireita, x, y);
                mapx -= 1;
                scroll_bkg(-1, 0);                  
            }
              
        }
        if(joypad() & J_RIGHT){
            if(x < 129){
                x += 1;
                principaldireita.spritids[0] = 8;
                principaldireita.spritids[1] = 9;
                principaldireita.spritids[2] = 10;
                principaldireita.spritids[3] = 11;

                for(i = 0; i < 4; i++) set_sprite_prop(principaldireita.spritids[i], S_PRIORITY);

                movegamecharacter(&principalatras, -10, -10);
                movegamecharacter(&principalfrente, -10, -10);
                movegamecharacter(&principaldireita, x, y);
                mapx += 1;
                scroll_bkg(1, 0);
            }
        }
        if(joypad() & J_UP){
            if(y > 23){
                y -= 1;

                movegamecharacter(&principalfrente, -10, -10);
                movegamecharacter(&principaldireita, -10, -10);
                movegamecharacter(&principalatras, x, y);

                mapy -= 1;
                scroll_bkg(0, -1); 
            }
        }
        if(joypad() & J_DOWN ){
            if(y < 139){
                y += 1;
                
                movegamecharacter(&principalatras, -10, -10);
                movegamecharacter(&principaldireita, -10, -10);
                movegamecharacter(&principalfrente, x, y);

                mapy += 1;
                scroll_bkg(0, 1);
            }

        }
        if(joypad() & J_A){
            printf("%u %u\n",(UINT16)(x),(UINT16)(y));
            printf("%u %u\n",(UINT16)mapx,(UINT16)mapy); 
        }
       performantdelay(6);      
    }

}