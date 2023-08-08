//
// Player.hpp
// Scrabble
//

#pragma once

#include "PlayerTile.h"
#include "Board.h"
#include "../Scrabble_Defs.h"

const int MAX_TILES = 7;
typedef enum {
	WAITING=0,
	MOVEMENT,
	IN_BOARD
}TileStatus;
/**
* CLASS Player
* Classe que permite guardar el estado de cada jugador
* Los datos que contiene son:
* la puntuacion del jugador, las fichas del jugador
* si hay alguna jugada en proceso
* si hay alguna ficha en movimiento
* la posicion X iniicial de las fichas en "la mano"
* 
* Tiene metodos para:
* inicializar el juego
* Saber la puntuacionm si hay alguna jugada
* cambiar el estado a movimiento
* saber si hay fichas en juego
* actualizar el estado de las fichas y enviarlas al tablero
* imprimir las fichas en movimiento y en la mano
* devolver las fichas a la mano, y tambien mezclar las fichas
* coger fichas de la bolsa
 */
class Player
{
public:
	Player();
	~Player() {}
	
	void inicialitza(vector<Tile>& fitxes);

	void setScore(int score) { m_score = score; }
	void setAlgunaJugada(bool cond) { m_algunaJugada = cond; };

	void toMove(int i);

	void algunaJugada();

	void actAlTauler(float mousePosX, float mousePosY, bool mouseIsPressed, Board& board, int i);
	void update(float mousePosX, float mousePosY, bool mouseIsPressed, Board& board);
	void render();
	void renderTileInMov(float posX, float posY, char letter);
	void renderTileStatic( float posX, float posY, char letter);

	void recall(int i);
	void shuffle();
	void rellenar(Tile t, int i);

	//bool finalitza();
	
	int getScore() const { return m_score; }
	bool getAlgunaJugada() const { return m_algunaJugada; };
	PlayerTile getPlayerTile(int i) const { return m_tiles[i]; };
private:
	int m_score;
	PlayerTile m_tiles[MAX_TILES];

	bool m_algunaJugada;
	bool m_moviment;
	float m_posInicalsX[MAX_TILES];//posicions on van les fitxes grans(no cambia)

	

};

//bool getInBoard(int i) const { return m_inBoard[i]; };
//void setInBoard(int i, bool cond) { m_inBoard[i] = cond; };

//void setPlayerTile(int i, PlayerTile t) { m_tiles[i] = t; };

//bool getMoviment() { return m_moviment; };

//float getPosIniciX(int i) { return m_posInicalsX[i]; };

//bool m_inBoard[MAX_TILES];
/*
TileStatus m_tileStatus[MAX_TILES]; //0 esperando a ser cogida 1 en desplazamiento 2 en el tablero
int m_tileStatus[MAX_TILES]; //1 esperando a ser cogida 2 en desplazamiento 3 en el tablero
int m_iPosX[MAX_TILES];
int m_iPosY[MAX_TILES];
*/