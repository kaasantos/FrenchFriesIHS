#include <gb/gb.h>

//generical character structure: id, position, graphics
struct GameCharacter{
	UBYTE spritids[4]; // all characters use 4 sprites
	UINT8 largura;
	UINT8 comprimento;
};

struct Boneca{
	UBYTE spritids[6]; // all characters use 4 sprites
	UINT8 largura;
	UINT8 comprimento;
};

struct scorePoint{
	UBYTE spriteids[9];
	UINT16 valor;
    UBYTE spriteTiles[11];
};