//
// PlayerTile.cpp
// Scrabble
//

#include "PlayerTile.h"
/**
* Constructor con parametros
*/
PlayerTile::PlayerTile(
	const Tile& tile,
	const bool empty,
	const float X,
	const float Y
)
{
	m_tile = tile;
	m_isEmpty = empty;
	m_posX = X;
	m_posY = Y;
	m_isOnBoard = false;
	m_boardPosition;
}
