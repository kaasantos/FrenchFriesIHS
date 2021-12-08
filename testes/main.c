#include <gb/gb.h>
#include <stdio.h>
#include "GameCharacter.c" //Criação das structs
#include "characters.c" //Sprites e frames dos personagens
#include "background.c" //Sprites do mapa
#include "mapbackground.c" //Geração do mapa com os sprites definidos no background

struct GameCharacter principalfrente;
struct GameCharacter principalatras;
struct GameCharacter principaldireita;
UBYTE spritesize = 8;
UINT8 x = 70;
UINT8 y = 140;

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


void setupatras(){
    principalatras.comprimento = 16;
    principalatras.largura = 16;
    principalatras.flagM = 0;

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
    principalfrente.flagM = 0;

    set_sprite_tile(4,4);
    principalfrente.spritids[0] = 4;
    set_sprite_tile(5,5);
    principalfrente.spritids[1] = 5;
    set_sprite_tile(6,6);
    principalfrente.spritids[2] = 6;
    set_sprite_tile(7,7);
    principalfrente.spritids[3] = 7;

    //movegamecharacter(&principalatras, x, y);
}

void setupdireita(){
    principaldireita.comprimento = 16;
    principaldireita.largura = 16;
    principaldireita.flagM = 0;

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

void main(){
    INT8 mapx = 44;
    INT8 mapy = 112;
    INT8 i;
    set_bkg_data(0, 10, TileLabel);
    set_bkg_tiles(0, 0, 32, 32, mapbackground);
    scroll_bkg(mapx,mapy);
    SHOW_BKG;

    set_sprite_data(0, 45, characters);
    setupfrente();
    setupatras();
    setupdireita();
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
            
            movegamecharacter(&principalatras, 0, 0);
            movegamecharacter(&principalfrente, 0, 0);
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
            movegamecharacter(&principalatras, 0, 0);
            movegamecharacter(&principalfrente, 0, 0);
            movegamecharacter(&principaldireita, x, y);
            mapx += 1;
            scroll_bkg(1, 0);
        }
        if(joypad() & J_UP){
            y -= 1;
            //movegamecharacter(&principalesquerda, 0, 0);
            movegamecharacter(&principalfrente, 0, 0);
            movegamecharacter(&principaldireita, 0, 0);
            movegamecharacter(&principalatras, x, y);
            mapy -= 1;
            scroll_bkg(0, -1); 
        }
        if(joypad() & J_DOWN){
            y += 1;
            //movegamecharacter(&principalesquerda, 0, 0);
            movegamecharacter(&principalatras, 0, 0);
            movegamecharacter(&principaldireita, 0, 0);
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