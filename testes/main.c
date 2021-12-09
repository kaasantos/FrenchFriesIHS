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
/*struct GameCharacter botfrente;
struct GameCharacter botatras;
struct GameCharacter botdireita; */

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
}

void main(){
    INT8 mapx = 44;
    INT8 mapy = 112;
    INT8 i;
    set_bkg_data(0, 33, TileLabel);
    set_bkg_tiles(0, 0, 32, 32, mapbackground);
    scroll_bkg(mapx,mapy);
    SHOW_BKG;

    set_sprite_data(0, 45, characters);
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
            
            movegamecharacter(&principalatras, -10, -10);
            movegamecharacter(&principalfrente, -10, -10);
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
            movegamecharacter(&principalatras, -10, -10);
            movegamecharacter(&principalfrente, -10, -10);
            movegamecharacter(&principaldireita, x, y);
            mapx += 1;
            scroll_bkg(1, 0);
        }
        if(joypad() & J_UP){
            y -= 1;
            movegamecharacter(&principalfrente, -10, -10);
            movegamecharacter(&principaldireita, -10, -10);
            movegamecharacter(&principalatras, x, y);
            mapy -= 1;
            scroll_bkg(0, -1); 
        }
        if(joypad() & J_DOWN){
            y += 1;
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
        //if(x <= 30 & y <= 45) movegamecharacter(&capanga1, 70, 20);   


       performantdelay(6);      
    }

}