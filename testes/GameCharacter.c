#include <gb/gb.h>

//generical character structure: id, position, graphics
struct GameCharacter{
	UBYTE spritids[4]; // all characters use 4 sprites
	UINT8 largura;
	UINT8 comprimento;
};

struct Boneca{
	UBYTE spritids[4]; // all characters use 4 sprites
	UINT8 largura;
	UINT8 comprimento;
};

struct ScorePoint{
	UBYTE spritids[9];
	UINT16 valor;
    UBYTE spriteTiles[12];
};