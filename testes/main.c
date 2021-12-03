#include <gb/gb.h>
#include <stdio.h>
#include "GameCharacter.c"
#include "GameSprites.c"

struct GameCharacter principalfrente;
struct GameCharacter principalatras;
struct GameCharacter principaldireita;
struct GameCharacter principalesquerda;
UBYTE spritesize = 8;
UINT8 x = 60;
UINT8 y = 130;


void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void movegamecharacter(struct GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spritesize, y);
    move_sprite(character->spritids[2], x, y + spritesize);
    move_sprite(character->spritids[3], x + spritesize, y + spritesize);
}


void setupfrente(){
    principalfrente.comprimento = 16;
    principalfrente.largura = 16;

    set_sprite_tile(0,0);
    principalfrente.spritids[0] = 0;
    set_sprite_tile(1,1);
    principalfrente.spritids[1] = 1;
    set_sprite_tile(2,2);
    principalfrente.spritids[2] = 2;
    set_sprite_tile(3,3);
    principalfrente.spritids[3] = 3;

    //movegamecharacter(&principalfrente, x, y);

}

void setupatras(){
    principalatras.comprimento = 16;
    principalatras.largura = 16;

    set_sprite_tile(4,4);
    principalatras.spritids[0] = 4;
    set_sprite_tile(5,5);
    principalatras.spritids[1] = 5;
    set_sprite_tile(6,6);
    principalatras.spritids[2] = 6;
    set_sprite_tile(7,7);
    principalatras.spritids[3] = 7;

    movegamecharacter(&principalatras, x, y);
}

void setupdireita(){
    principaldireita.comprimento = 16;
    principaldireita.largura = 16;

    set_sprite_tile(8,8);
    principaldireita.spritids[0] = 8;
    set_sprite_tile(9,9);
    principaldireita.spritids[1] = 9;
    set_sprite_tile(10,10);
    principaldireita.spritids[2] = 10;
    set_sprite_tile(11,11);
    principaldireita.spritids[3] = 11;

    //movegamecharacter(&principaldireita, x, y);
}

void setupesquerda(){
    principalesquerda.comprimento = 16;
    principalesquerda.largura = 16;

    set_sprite_tile(12,12);
    principalesquerda.spritids[0] = 12;
    set_sprite_tile(13,13);
    principalesquerda.spritids[1] = 13;
    set_sprite_tile(14,14);
    principalesquerda.spritids[2] = 14;
    set_sprite_tile(15,15);
    principalesquerda.spritids[3] = 15;

    //movegamecharacter(&principalesquerda, x, y);

}


void main(){
    set_sprite_data(0, 16, GameSprites);
    setupfrente();
    setupatras();
    setupdireita();
    setupesquerda();



    SHOW_SPRITES;
    DISPLAY_ON;

    while(1){
        if(joypad() & J_LEFT){
            x -= 2;
            movegamecharacter(&principaldireita, 0, 0);
            movegamecharacter(&principalatras, 0, 0);
            movegamecharacter(&principalfrente, 0, 0);
            movegamecharacter(&principalesquerda, x, y);
        }
        if(joypad() & J_RIGHT){
           x += 2;
            movegamecharacter(&principalesquerda, 0, 0);
            movegamecharacter(&principalatras, 0, 0);
            movegamecharacter(&principalfrente, 0, 0);
            movegamecharacter(&principaldireita, x, y);
        }
        if(joypad() & J_UP){
            y -= 2;
            movegamecharacter(&principalesquerda, 0, 0);
            movegamecharacter(&principalfrente, 0, 0);
            movegamecharacter(&principaldireita, 0, 0);
            movegamecharacter(&principalatras, x, y);
        }
        if(joypad() & J_DOWN){
            y += 2;
            movegamecharacter(&principalesquerda, 0, 0);
            movegamecharacter(&principalatras, 0, 0);
            movegamecharacter(&principaldireita, 0, 0);
            movegamecharacter(&principalfrente, x, y);
        }

       performantdelay(6);      
    }

}