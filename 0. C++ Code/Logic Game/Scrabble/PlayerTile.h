//
// PlayerTile.hpp
// Scrabble
//

#pragma once

#include "Tile.h"
#include "BoardPosition.h"
#include "../GraphicManager.h"
#include "../Scrabble_Defs.h"

/**
* CLASS PlayerTile
* Classe que permite guardar una ficha de un jugador
* Los datos que contiene son:
* la ficha, si esta en su posicion inicial
* la posicion en cada momento, si esta en el tablero
* y la posicion en este
*
* Tiene metodos para:
* saber todos los datos mencionados antes
* y poder editarlos, ademas de un constructor
* por defecto y uno con parametros
 */
class PlayerTile
{
public:
	PlayerTile() { m_isEmpty = false; m_posX = 0; m_posY = 0; m_isOnBoard = false; };
	PlayerTile(
		const Tile& tile,
		const bool empty,
		const float X,
		const float Y
	);
	~PlayerTile() {}
	
	bool getEmpty() const { return m_isEmpty; }
	float getX() const { return m_posX; }
	float getY() const { return m_posY; }
	bool getOnBoard() const { return m_isOnBoard; }
	Tile getTile() const { return m_tile; }
	BoardPosition getBoardPosition() const { return m_boardPosition; }
	
	void setTile(const Tile& t) { m_tile = t; }
	void setEmpty(const bool empty) { m_isEmpty = empty; }
	void setPos(const float X, const float Y) { m_posX = X; m_posY = Y; }
	void setOnBoard(const bool onBoard) { m_isOnBoard = onBoard; }
	void setBoardPosition(const BoardPosition& boardPos) { m_boardPosition = boardPos; }
private:
	Tile m_tile;
	bool m_isEmpty;
	float m_posX, m_posY;
	bool m_isOnBoard;
	BoardPosition m_boardPosition;
};