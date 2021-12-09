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

//multiplayer
int wait_for_connection(){
    receive_byte();
    int out = 0,pad;
    while(!out){
        pad = joypad();
        if(pad == J_A || pad == J_B)
            out = 1;
    }
    if(pad == J_A){
        _io_out = pad;
        send_byte();
        while(_io_status == IO_SENDING){;}
        receive_byte();
        while(_io_status == IO_RECEIVING){;}
        return 1;
    }
    
    if(pad == J_B){
        while(_io_status == IO_RECEIVING){;}
        _io_out = 1;
        send_byte();
        while(_io_status == IO_SENDING){;}
        return 0;
    }
}
//multiplayer
int send_data(int *data,int num_dados){
    for(int i=0;i < num_dados; i++){
        _io_out = data[i];
        delay(1);
        send_byte();
        while(_io_status == IO_SENDING){;}
        receive_byte();
        while(_io_status == IO_RECEIVING){;}
        if(_io_in != OK)
            return NOT_OK;
    }
    return OK;
}
//multiplayer
int recieve_data(int*recieved, int num_dados){
    for(int i=0;i < num_dados; i++){
        receive_byte();
        while(_io_status == IO_RECEIVING){;}
        recieved[i] = _io_in;
        _io_out = OK;
        delay(1);
        send_byte();
        while(_io_status == IO_SENDING){;}
    }
    return OK;
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

<<<<<<< HEAD
    set_sprite_data(0, 45, characters);
=======
    // int playerMultiplayerL_Or_R = wait_for_connection();

    set_sprite_data(0, 46, characters);
>>>>>>> d8ff5a11ea08cb8231482346664b90586f3dfee1
    setups();
    SHOW_SPRITES;

    DISPLAY_ON;

    while(1){
        //multiplayer
        //primeiro jogador
        // if(playerMultiplayerL_Or_R==0){  
            //int input[1];
            // recieve_data(input,1);


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

<<<<<<< HEAD
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

=======
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
            //multiplayer
            //movimentos do segundo jogador na tela principal
            // andar pra esquerda 1, cima 2, direita 3, baixo 4, parado 0
            // if(input[0]==1){
            // movimentação segundo pra esquerda}
            // if(input[0]==2){
            // movimentação segundo pra cima}
            // if(input[0]==3){
            // movimentação segundo pra direita}
            // if(input[0]==4){
            // movimentação segundo pra baixo}

            performantdelay(6); 
            //multiplayer
            /*
            int data[19];
            data[0] = pode_andar;
            data[1] = primeirojogador.x[0];
            data[2] = primeirojogador.x[1];
            data[3] = primeirojogador.x[2];
            data[4] = primeirojogador.x[3];
            data[5] = primeirojogador.y[0];
            data[6] = primeirojogador.y[1];
            data[7] = primeirojogador.y[2];
            data[8] = primeirojogador.y[3];
            data[9] = primeirojogador.x[0];
            data[10] = segundojogador.x[1];
            data[11] = segundojogador.x[2];
            data[12] = segundojogador.x[3];
            data[13] = segundojogador.y[0];
            data[14] = segundojogador.y[1];
            data[15] = segundojogador.y[2];
            data[16] = segundojogador.y[3];
            data[17] = SCORE_Primeiro;//para decidir quem venceu(quem chegar primeiro ganha)
            data[18] = SCORE_Segundo;//para decidir quem venceu(quem chegar primeiro ganha)
            send_data(data, 19);

            if(SCORE_Primeiro == 1 || SCORE_Segundo == 1){
                if(SCORE_Primeiro == 1)
                    printf("\n\n\n\n\n\n\n      Parabens\n    JOGADOR UM\n    voce venceu!");
                else
                    printf("\n\n\n\n\n\n\n\n    JOGADOR DOIS\n    venceu!");
                //Esconder os sprites
                HIDE_SPRITES;
                while(1){
                    WORD pad = joypad();
                    if(pad) 
                    break;
                }
                if((SCORE_Primeiro == 1) || (SCORE_Segundo == 1)){
                    break;
                }
            }

        }//segundo jogador
        else{

            int input[1];
            input[0] = 0;
            if (joypad() & J_LEFT)
            { 
                input[0]=1;
            }
            if (joypad() & J_UP)
            { 
                input[0]=2;
            }
            if (joypad() & J_RIGHT)
            { 
                input[0]=3;
            }
            if (joypad() & J_DOWN)
            { 
                input[0]=4;
            }
            send_data(input,1);

            int datarecieve[19];
            recieve_data(datarecieve, 19);

            pode_andar = datarecieve[0];
            primeirojogador.x[0] = datarecieve[1];
            primeirojogador.x[1] = datarecieve[2];
            primeirojogador.x[2] = datarecieve[3];
            primeirojogador.x[3] = datarecieve[4];
            primeirojogador.y[0] = datarecieve[5];
            primeirojogador.y[1] = datarecieve[6];
            primeirojogador.y[2] = datarecieve[7];
            primeirojogador.y[3] = datarecieve[8];
            segundojogador.x[0] = datarecieve[9];
            segundojogador.x[1] = datarecieve[10];
            segundojogador.x[2] = datarecieve[11];
            segundojogador.x[3] = datarecieve[12];
            segundojogador.y[0] = datarecieve[13];
            segundojogador.y[1] = datarecieve[14];
            segundojogador.y[2] = datarecieve[15];
            segundojogador.y[3] = datarecieve[16];
            SCORE_Primeiro = datarecieve[17];
            SCORE_Segundo = datarecieve[8]; 

            if(SCORE_Primeiro == 1 || SCORE_Segundo == 1){
                if(SCORE_Segundo == 1)
                    printf("\n\n\n\n\n\n\n      Parabens\n    JOGADOR DOIS\n    voce venceu!");
                else
                    printf("\n\n\n\n\n\n\n\n    JOGADOR UM\n    venceu!");
                //Esconder os sprites
                HIDE_SPRITES;
                while(1){
                    WORD pad = joypad();
                    if(pad) 
                    break;
                }
                if((SCORE_Primeiro == 1) || (SCORE_Segundo == 1)){
                    break;
                }
            }

            //movimentação dos sprites com base no datarecieve
        }  */
>>>>>>> d8ff5a11ea08cb8231482346664b90586f3dfee1

       performantdelay(6);      
    }

}