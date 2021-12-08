#include <gb/gb.h>
#include <stdio.h>
#include "GameCharacter.c" //Criação das structs
#include "characters.c" //Sprites e frames dos personagens
#include "background.c" //Sprites do mapa
#include "mapbackground.c" //Geração do mapa com os sprites definidos no background

struct GameCharacter principalfrente;
struct GameCharacter principalatras;
struct GameCharacter principaldireita;
struct Boneca bonecafixa; 
struct Boneca bonecafrente;
struct Boneca bonecatras; 
struct GameCharacter capanga1;
struct GameCharacter capanga2frente;
struct GameCharacter capanga2costas;
struct GameCharacter botfrente;
struct GameCharacter botatras;
struct GameCharacter botdireita;

UBYTE spritesize = 8;
UINT8 x = 70;
UINT8 y = 140;

void performantdelay(UINT8 numloops){
    UINT8 j;
    for(j = 0; j < numloops; j++){
        wait_vbl_done();
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
    principalatras.comprimento = 16;
    principalatras.largura = 16;

    set_sprite_tile(0,0);
    principalatras.spritids[0] = 0;
    set_sprite_tile(1,1);
    principalatras.spritids[1] = 1;
    set_sprite_tile(2,2);
    principalatras.spritids[2] = 2;
    set_sprite_tile(3,3);
    principalatras.spritids[3] = 3;

    movegamecharacter(&principalatras, x, y);

}

void setupfrente(){
    principalfrente.comprimento = 16;
    principalfrente.largura = 16;

    set_sprite_tile(4,4);
    principalfrente.spritids[0] = 4;
    set_sprite_tile(5,5);
    principalfrente.spritids[1] = 5;
    set_sprite_tile(6,6);
    principalfrente.spritids[2] = 6;
    set_sprite_tile(7,7);
    principalfrente.spritids[3] = 7;
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
}

void setupbonecafrente(){
    bonecafrente.comprimento = 16;
    bonecafrente.largura = 24;

    set_sprite_tile(23, 23);
    bonecafrente.spritids[0] = 24;
    set_sprite_tile(24, 24);
    bonecafrente.spritids[1] = 25;
    set_sprite_tile(25, 25);
    bonecafrente.spritids[2] = 26;
    set_sprite_tile(26, 26);
    bonecafrente.spritids[3] = 27;
    set_sprite_tile(27, 27);
    bonecafrente.spritids[4] = 28;
    set_sprite_tile(28, 28);
    bonecafrente.spritids[5] = 29;

    //movegamecharacterboneca(&bonecafrente, 72, 27);
}

void setupbonecatras(){
    bonecatras.comprimento = 16;
    bonecatras.largura = 24;

    set_sprite_tile(29, 29);
    bonecatras.spritids[0] = 30;    
    set_sprite_tile(30, 30);
    bonecatras.spritids[1] = 31; 
    set_sprite_tile(31, 31);
    bonecatras.spritids[2] = 32; 
    set_sprite_tile(32, 32);
    bonecatras.spritids[3] = 33;
    set_sprite_tile(27, 27);
    bonecatras.spritids[4] = 28;
    set_sprite_tile(28, 28);
    bonecatras.spritids[5] = 29;
}

void setupbonecafixa(){
    bonecafixa.comprimento = 16;
    bonecafixa.largura = 24;

    set_sprite_tile(33, 23);
    bonecafixa.spritids[0] = 24;
    set_sprite_tile(34, 24);
    bonecafixa.spritids[1] = 25;
    set_sprite_tile(35, 25);
    bonecafixa.spritids[2] = 26;
    set_sprite_tile(36, 26);
    bonecafixa.spritids[3] = 27;
    set_sprite_tile(37, 27);
    bonecafixa.spritids[4] = 28;
    set_sprite_tile(38, 28);
    bonecafixa.spritids[5] = 29;

    movegamecharacterboneca(&bonecafixa, 10, 130);
}

void setups(){
    setupfrente();
    setupatras();
    setupdireita();
    setupbonecafrente();
    setupbonecatras();
    setupbonecafixa();
}

void main(){
    INT8 mapx = 44;
    INT8 mapy = 112;
    INT8 i;
    set_bkg_data(0, 10, TileLabel);
    set_bkg_tiles(0, 0, 32, 32, mapbackground);
    scroll_bkg(mapx,mapy);
    SHOW_BKG;

    set_sprite_data(0, 46, characters);
    setups();
    SHOW_SPRITES;

    DISPLAY_ON;

    while(1){
        if(joypad() & J_LEFT){
            x -= 1;
            principaldireita.spritids[1] = 8;
            principaldireita.spritids[0] = 9;
            principaldireita.spritids[3] = 10;
            principaldireita.spritids[2] = 11;

            for(i = 0; i < 4; i++) set_sprite_prop(principaldireita.spritids[i], S_FLIPX);

           /* if(principaldireita.flagM = 0){
                principaldireita.spritids[3] = 10;
                principaldireita.spritids[2] = 11;

                principaldireita.flagM = 1;
            }else{
                principaldireita.spritids[3] = 11;
                principaldireita.spritids[2] = 10;

                set_sprite_prop(principaldireita.spritids[2], S_FLIPX);
                set_sprite_prop(principaldireita.spritids[3], S_FLIPX);

                principaldireita.flagM = 0;
            } */
            
            //movegamecharacter(&principaldireita, 0, 0);
            
            movegamecharacter(&principalatras, -10, -10);
            movegamecharacter(&principalfrente, -10, -10);
            //movegamecharacter(&principalesquerda, x, y);
            movegamecharacter(&principaldireita, x, y);
            mapx -= 1;
            scroll_bkg(-1, 0);        
        }
        if(joypad() & J_RIGHT){
            x += 1;
            principaldireita.spritids[0] = 8;
            principaldireita.spritids[1] = 9;
            principaldireita.spritids[2] = 10;
            principaldireita.spritids[3] = 11;

            for(i = 0; i < 4; i++) set_sprite_prop(principaldireita.spritids[i]);
            //movegamecharacter(&principalesquerda, 0, 0);
            movegamecharacter(&principalatras, -10, -10);
            movegamecharacter(&principalfrente, -10, -10);
            movegamecharacter(&principaldireita, x, y);
            mapx += 1;
            scroll_bkg(1, 0);
        }
        if(joypad() & J_UP){
            y -= 1;
            //movegamecharacter(&principalesquerda, 0, 0);
            movegamecharacter(&principalfrente, -10, -10);
            movegamecharacter(&principaldireita, -10, -10);
            movegamecharacter(&principalatras, x, y);
            mapy -= 1;
            scroll_bkg(0, -1); 
        }
        if(joypad() & J_DOWN){
            y += 1;
            //movegamecharacter(&principalesquerda, 0, 0);
            movegamecharacter(&principalatras, -10, -10);
            movegamecharacter(&principaldireita, -10, -10);
            movegamecharacter(&principalfrente, x, y);
            mapy += 1;
            scroll_bkg(0, 1);
        }
        if(joypad() & J_A){
            printf("%u %u\n",(UINT16)(x),(UINT16)(y));
            printf("%u %u %u\n",(UINT16)mapx,(UINT16)mapy); 
        }    

       performantdelay(6);      
    }

}