#include <gb/gb.h>

//generical character structure: id, position, graphics
struct GameCharacter {
	UBYTE spritids[4]; // all characters use 4 sprites
	UINT8 largura;
	UINT8 comprimento;
};