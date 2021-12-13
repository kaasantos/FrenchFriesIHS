#include <gb/gb.h>
#include <stdio.h>
#include "sqgame3_data.c"
#include "sqgame3_map.c"//tela inicio
#include "GameCharacter.c" //Criação das structs
#include "characters.c" //Sprites e frames dos personagens e score
#include "background.c" //Sprites do mapa
#include "mapbackground.c" //Geração do mapa com os sprites definidos no background
#include "score.c"
#include "sons.c" //configurações de sons
#include "fadedelay.c"//configurações do fade e do performantdelay

struct GameCharacter principalfrente;
struct GameCharacter principalatras;
struct GameCharacter principaldireita;
struct GameCharacter bonecafixa; 
struct GameCharacter bonecafixaback;
struct GameCharacter botfrente;
struct GameCharacter botatras;
struct GameCharacter botdireita;
struct ScorePoint timer;

UBYTE spritesize = 8;
UINT8 x = 76, y = 135, mapx = 44, mapy = 112, count = 0;
UINT16 time = 1;



void movegamecharacter(struct GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spritesize, y);
    move_sprite(character->spritids[2], x, y + spritesize);
    move_sprite(character->spritids[3], x + spritesize, y + spritesize);
}

void movetimer(struct ScorePoint *timer, UINT8 x, UINT8 y){
    //UINT8 i = 0;
    move_sprite(timer->spritids[0], x + 2*spritesize, y);
    move_sprite(timer->spritids[1], x + 3*spritesize, y);
    move_sprite(timer->spritids[2], x + 4*spritesize, y);
    move_sprite(timer->spritids[3], x + 5*spritesize, y);
    move_sprite(timer->spritids[4], x + 6*spritesize, y);
    move_sprite(timer->spritids[5], x + 7*spritesize, y);
    move_sprite(timer->spritids[6], x + 8*spritesize, y);
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
    
    for(z = 22; z < 27; z++){
        set_sprite_tile(z,z);
        timer.spritids[w] = z;
        w++;
    }
    set_sprite_tile(27,27);
    set_sprite_tile(28,28);
    set_sprite_tile(29,29);
    set_sprite_tile(30,30);    
    set_sprite_tile(31,31);
    set_sprite_tile(32,32);
    set_sprite_tile(33,33);
    set_sprite_tile(34,34);
    set_sprite_tile(35,35);
    set_sprite_tile(36,36);
    timer.spritids[5] = 36;
    set_sprite_tile(37,37);
    timer.spritids[6] = 37;

    for(z = 0; z < 11; z++){
        timer.spriteTiles[z] = aux;
        aux++;
    }

    movetimer(&timer, 96, 152);
    //move
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

void lose(){
    HIDE_SPRITES;
    performantdelay(5);
    scroll_bkg(-mapx, -40-mapy);
    printf("      S#F@D3U");
}

void victory(){
    HIDE_SPRITES; 
    performantdelay(5);
    scroll_bkg(-mapx, -40-mapy);
    printf("    Voce venceu.\n    Why so easy??");   
}

void main(){
    INT8 i, flag = 0, derrota = 2;
    UINT16 tras = 4, amimir = 4, frente = 3, acordar = 3, virada = 0;

    NR52_REG = 0x80; // liga o som
    NR50_REG = 0x77; // volume máximo
    NR51_REG = 0xFF; // canais que estão sendo usados(todos)

    set_bkg_data(0, 114, sqgame3_data);
    set_bkg_tiles(0, 0, 20, 18, sqgame3_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);
    somSelect();
    fadeout();

    set_bkg_data(0, 35, TileLabel);
    set_bkg_tiles(0, 0, 32, 32, mapbackground);  	
    scroll_bkg(mapx,mapy);

	fadein();

    set_sprite_data(0, 42, characters);
    setups();
     
    SHOW_SPRITES;

    while(derrota != 12 && y > 30){
        if(joypad() & J_LEFT){
            if(x > 28 ){
                somAndar();
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
                if(virada == 1){
                    movegamecharacter(&principaldireita, -10, -10);
                    lose();
                    break;
                }               
            }       
        }
        if(joypad() & J_RIGHT){
            if(x < 129){
                somAndar();
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

                if(virada == 1){
                    movegamecharacter(&principaldireita, -10, -10);
                    lose();
                    break;
                } 
            }
        }
        if(joypad() & J_UP){
            if(y > 23){
                somAndar();
                y -= 1;

                movegamecharacter(&principalfrente, -10, -10);
                movegamecharacter(&principaldireita, -10, -10);
                movegamecharacter(&principalatras, x, y);

                mapy -= 1;
                scroll_bkg(0, -1); 

                if(virada == 1){
                    movegamecharacter(&principalatras, -10, -10);
                    lose();
                    break;
                } 
            }
        }
        if(joypad() & J_DOWN ){
            if(y < 139){
                somAndar();
                y += 1;
                
                movegamecharacter(&principalatras, -10, -10);
                movegamecharacter(&principaldireita, -10, -10);
                movegamecharacter(&principalfrente, x, y);

                mapy += 1;
                scroll_bkg(0, 1);

                if(virada == 1){
                    movegamecharacter(&principalfrente, -10, -10);
                    lose();
                    break;
                } 
            }
        }
        if(joypad() & J_A){
            //somViraVolta();
            printf("%u %u\n",(UINT16)(x),(UINT16)(y));
            printf("%u %u\n",(UINT16)mapx,(UINT16)mapy); 
            //game = 0;
        }
        if(joypad() & J_B){
            somVira();
            //game = 2;
        }

        if(count>=10){ 
            if(flag == 10){
                flag = 0;
                set_sprite_tile(timer.spritids[5], timer.spriteTiles[derrota]);
                derrota++;
            }
            time++;
            flag++;
            //printf("Tempo: %d\n",time);
            count = 0;
        }
        count++;

        set_sprite_tile(timer.spritids[6], timer.spriteTiles[flag]);

        if(y < 100 && y >= 80) amimir = 3;
        if(y < 80 && y <= 60) amimir = 2;
        if(y < 60) amimir = 1;

        if(time == tras && count == 1){
            movegamecharacter(&bonecafixaback, 10, 130);
            movegamecharacter(&bonecafixa, 0, 0);
            somViraVolta(); 
            virada = 0;
            frente = tras + amimir;
        }else if(time == frente && count == 1){
            movegamecharacter(&bonecafixa, 10, 130);
            movegamecharacter(&bonecafixaback, 0, 0);
            somVira(); 
            virada = 1;
            tras = frente + acordar;
        }

        performantdelay(6);      
    }

    if(derrota == 12) lose();
    if(y <= 30) victory();
}
