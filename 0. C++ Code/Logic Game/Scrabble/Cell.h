//
//  Cell.hpp
//  Scrabble
//


#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include "Tile.h"
#include "../Scrabble_Defs.h"
#include "../GraphicManager.h"

typedef enum {
    DL = 0,
    TL,
    DW,
    TW,
    NO_EFFECT
} ScoreEffect;

/**
* CLASS Cell
* Classe que permite guardar informacion de una
* casilla del tablero
* el tipo de efecto, si esta vacia, si hay
* una ficha que se esta jugando, y si hay, la ficha
* que se encuentra ahi
*
* Tiene metodos para:
* saber el estado de los atributos mencionados
* anetriormente, cambiar estos mismos,
* y un render que permite imprimir las celdas
 */
class Cell
{
public:
    Cell() { m_empty = true; m_tilePlayed = false; m_tile; m_scoreEffect = ScoreEffect::NO_EFFECT; };
    ~Cell() {};

   
    void setTile(Tile tile) { m_tile = tile; };
    void setEmpty(bool c) { m_empty = c; };
    void setScoreEffect(ScoreEffect x) { m_scoreEffect = x; };
    void setTilePlayed(bool c) { m_tilePlayed = c; };
  
    void render(float posX, float posY);

    ScoreEffect getScoreEffect() const { return m_scoreEffect; };
    bool getEmpty() const { return m_empty; };
    bool getTilePlayed() const { return m_tilePlayed; };
    Tile getTile() const { return m_tile; };
private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty; // true si esta vacia false si esta ocupada
    bool m_tilePlayed;// false si esta en construccion y true si ya esta construida
};


#endif /* Cell_hpp */
//void setTile(char letter, int score) { m_tile.setLetter(letter); m_tile.setScore(score); };
  //void changeEmpty() { if (m_empty == true) m_empty = false; else m_empty = true; }
    //void changeTilePlayed() { if (m_tilePlayed == true) m_empty = false; else m_empty = true; };