#include"../Scrabble_Defs.h"

typedef enum {
	NORMAL = 0,
	IN_MOVEMENT,
	IN_BOARD,
	NONE
} TileButtonState;

class TileButton
{
public:
	TileButton() {};
	~TileButton() {}

	int update(int mousePosX, int mousePosY, bool mouseIsPressed);
	void render();
private:
	TileButtonState m_tileStatus; //1 esperando a ser cogida 2 en desplazamiento 3 en el tablero
	int m_iPosX;
	int m_iPosY;
	int m_posActX;
	int m_posActY;
};