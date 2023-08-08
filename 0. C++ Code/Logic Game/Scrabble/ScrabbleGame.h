//
//  ScrabbleGame.hpp
//  Letris
//
//  Created by Enric Vergara on 13/02/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#ifndef ScrabbleGame_hpp
#define ScrabbleGame_hpp

#include <stdio.h>

#include "Board.h"
#include "LettersBag.h"
#include "Player.h"
#include "Button.h"

#include "../Scrabble_Defs.h"
#include "../GraphicManager.h"


/**
* CLASS ScrabbleGame
* Classe que permet guardar el joc de l'scabble
* Les dades que conté són: tauler, jugadors, bolsa amb lletres,
* jugador actual, botons(RECALL, SHUFFLE, SEND, PASS)
* Conté mètodes per actualiztar el tauler, el correcte funcionament del joc
* i la "impresió" de la part grafica
 */
class ScrabbleGame
{
public:
    ScrabbleGame();
    ~ScrabbleGame();
    
    void updateAndRender (int mousePosX, int mousePosY,bool mouseStatus);
    void buttonSend();
    void buttonRecall();
    void buttonShuffle();
    void buttonPass();

    void showPlrData();
    void showErrMsg(const CurrentWordResult& errMsg, const int points);
    void endMsg(Player p[]);
private:
    Board m_board;
    Player m_players[NUM_PLAYERS];
    LettersBag m_lettersBag;
    int m_currentPlayer;
    Button m_buttonRecall;
    Button m_buttonShuffle;
    Button m_buttonsSend;
    Button m_buttonPass;

    bool m_final; //boleano para saber cuando llegamos al final de la partida
};

#endif /* ScrabbleGame_hpp */
