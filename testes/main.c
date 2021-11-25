#include <stdio.h>
#include <gb/gb.h>
#include "Faces.c"
#include "background.c"
#include "backgroundfiles.c"


void main(){
    UINT8 currentspriteindex = 0;

    set_bkg_data(0,7, backgroundfiles);
    set_bkg_tiles(0, 0, 40, 18, brackgroundmap);

    SHOW_BKG;
    DISPLAY_ON;

    set_sprite_data(0, 3, Faces);   //carregar variavel do faces, iniciando do 0, pegando até o segundo
    set_sprite_tile(0,0);
    move_sprite(0, 78, 88); //mover o sprite 0 para o sprite 88 de largura e 78 de comprimento
    SHOW_SPRITES;

    while(1){
        switch(joypad()){
            case J_LEFT:
                scroll_sprite(0,-1,0);
                break;
            case J_RIGHT:
                scroll_sprite(0,1,0);
                break;
            case J_UP:
                scroll_sprite(0,0,-1);
                break;
            case J_DOWN:
                scroll_sprite(0,0,1);
                break;
        }
        scroll_bkg(1,0);
        delay(100);
    }
}