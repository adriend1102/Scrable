//
//  Scrabble.h
//  MP_Practica
//
//  Created by Enric Vergara on 14/03/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#ifndef Scrabble_h
#define Scrabble_h

#include <vector>
#include "Scrabble/BoardPosition.h"

using namespace std;


// Screen size (W,H)=(750,850)
const int SCREEN_SIZE_X			= 750; 
const int SCREEN_SIZE_Y			= 850; 
const int BOARD_SIZE			= 600;
const int BOARD_COLS_AND_ROWS   = 15;
const int BOARD_TILE_SIZE       = BOARD_SIZE / BOARD_COLS_AND_ROWS;

const int BOARD_POS_X = SCREEN_SIZE_X * 0.5 - BOARD_SIZE * 0.5;
const int BOARD_POS_Y = 40;

const int btn_size_w = 139;
const int btn_size_h = 100;

const float POS_Y = SCREEN_SIZE_Y - 2 * btn_size_h;//constante eje Y donde van las piezas grandesd del jugador (siempre)

const int NUM_PLAYERS = 3;
typedef vector<BoardPosition> VectorOfPositions;


#endif /* Scrabble_h */
