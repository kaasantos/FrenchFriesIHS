#include <gb/gb.h>
#include <stdio.h>
#include "sqgame3_data.c"
#include "sqgame3_map.c"//tela inicio
#include "GameCharacter.c" //Criação das structs
#include "characters.c" //Sprites e frames dos personagens e score
#include "background.c" //Sprites do mapa
#include "mapbackground.c" //Geração do mapa com os sprites definidos no background
#include "score.c"

struct GameCharacter principalfrente;
struct GameCharacter principalatras;
struct GameCharacter principaldireita;
struct Boneca bonecafixa; 
struct Boneca bonecafixaback;
struct GameCharacter botfrente;
struct GameCharacter botatras;
struct GameCharacter botdireita;
struct ScorePoint timer;

UBYTE spritesize = 8;
UINT8 x = 76;
UINT8 y = 135;
UINT8 count = 0;
UINT16 time = 0;


void performantdelay(UINT8 numloops){
    UINT8 j;
    for(j = 0; j < numloops; j++){
        wait_vbl_done();
    }     
}

void fadeout(){
    UINT8 f;
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
    UINT8 f;
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

void movetimer(struct ScorePoint *timer, UINT8 x, UINT8 y){
    //UINT8 i = 0;
    move_sprite(timer->spritids[0], x, y);
    move_sprite(timer->spritids[1], x + spritesize, y);
    move_sprite(timer->spritids[2], x + 2*spritesize, y);
    move_sprite(timer->spritids[3], x + 3*spritesize, y);
    move_sprite(timer->spritids[4], x + 4*spritesize, y);
    move_sprite(timer->spritids[5], x + 5*spritesize, y);
    move_sprite(timer->spritids[6], x + 6*spritesize, y);
    move_sprite(timer->spritids[7], x + 7*spritesize, y);
    move_sprite(timer->spritids[8], x + 8*spritesize, y);
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

/* void setupbotfrente(){
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
} */

void setupbonecafixa(){
    INT8 z, w = 0;
    bonecafixa.comprimento = 16;
    bonecafixa.largura = 16;

    for(z = 12; z < 16; z++){
        set_sprite_tile(z,z);
        bonecafixa.spritids[w] = z;
        w++;
    }
    //movegamecharacterboneca(&bonecafixa, 10, 130);
} 

void setupbonecafixaback(){
    INT8 z, w = 0;
    bonecafixaback.comprimento = 16;
    bonecafixaback.largura = 16;

    for(z = 18; z < 22; z++) {
        set_sprite_tile(z,z);
        bonecafixaback.spritids[w] = z;
        w++;
    }

    movegamecharacter(&bonecafixaback, 10, 130);
}

void setuptimer(){
    INT8 z, w = 0, aux = 27;
    
    for(z = 22; z < 28; z++){
        set_sprite_tile(z,z);
        timer.spritids[w] = z;
        w++;
    }
    set_sprite_tile(28,28);
    set_sprite_tile(29,29);
    set_sprite_tile(30,30);    
    timer.spritids[6] = 30;
    set_sprite_tile(31,31);
    timer.spritids[7] = 31;
    set_sprite_tile(32,32);
    set_sprite_tile(33,33);
    set_sprite_tile(34,34);
    set_sprite_tile(35,35);
    set_sprite_tile(36,36);
    set_sprite_tile(37,37);
    set_sprite_tile(38,38);
    timer.spritids[8] = 38;

    for(z = 0; z < 12; z++){
        timer.spriteTiles[z] = aux;
        aux++;
    }

    movetimer(&timer, 96, 152);
    //move
}

void spritestimer(UINT16 tempinho){
    if(tempinho > 30) set_sprite_tile(timer.spritids[6],timer.spriteTiles[9]); 


    switch(tempinho){
        case 1:
            set_sprite_tile(timer.spritids[8], timer.spriteTiles[1]);
            break;
        case 2:
            set_sprite_tile(timer.spritids[8], timer.spriteTiles[2]);
            break;
    }

}

void setups(){
    setupfrente();
    setupatras();
    setupdireita();
    //setupbotatras();
    //setupbotfrente();
    //setupbotdireita();
    setupbonecafixa();
    setupbonecafixaback();
    setuptimer();
}

void main(){
    INT8 mapx = 44;
    INT8 mapy = 112;
    INT8 i;
    INT8 game = 1;

    set_bkg_data(0, 114, sqgame3_data);
    set_bkg_tiles(0, 0, 20, 18, sqgame3_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);
    fadeout();

    set_bkg_data(0, 35, TileLabel);
    set_bkg_tiles(0, 0, 32, 32, mapbackground);  	
    scroll_bkg(mapx,mapy);

	fadein();

    set_sprite_data(0, 42, characters);
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
            //game = 0;
        }
        if(joypad() & J_B){
            //game = 2;
        }

        if(count>=10){ 
            time++;
            //printf("Tempo: %d\n",time);
            count = 0;
        }
        count++;

        spritestimer(time);

        if(time == 5){
            movegamecharacter(&bonecafixa, 10, 130);
            movegamecharacter(&bonecafixaback, 0, 0);
        }else if(time == 10){
            movegamecharacter(&bonecafixa, 0, 0);
            movegamecharacter(&bonecafixaback, 10, 130);
        }

        performantdelay(6);  

        //tela de derrota quando game == 0( no momento apertando A "S")
        /*if(game ==0){
            HIDE_SPRITES;
            while(1){
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n              Se Ferrou!");
                performantdelay(25);
                if(joypad()){
                    break;
                }
            }
            break;
        }*/
        //tela de vitoria quando game == 2( no momento apertando B "A")
        /*if(game == 2){
            HIDE_SPRITES;
            while(1){
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n              Você venceu, f0f0!");
                performantdelay(25);
                if(joypad()){
                    break;
                }
            }
            break;
        } */
    }

}