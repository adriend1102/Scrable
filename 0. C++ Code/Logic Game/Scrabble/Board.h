//
//  Board.hpp
//  Scrabble
//


#ifndef Board_hpp
#define Board_hpp

#include "../Scrabble_Defs.h"
#include <stdio.h>
#include <string>


#include "Cell.h"
#include "Dictionary.h"
#include "BoardPosition.h"


using namespace std;

// (0,0) ----> X
//   |  (col:0, row:0), (col:1, row:0)
//   |  (col:0, row:1), (col:1, row:1)
//   |     <- Size X (width)->
//   |      Coordinate system
//   v
//   Y

typedef enum {
    VALID_POSITION = 0,
    INVALID_POSITION,
    NOT_EMPTY
} PositionResult;

typedef enum {
    ALL_CORRECT = 0,
    //Tiles must be vertically or horizontally aligned and together
    INVALID_NOT_ALIGNED,
    //At least one letter must be next to the rest of the words.
    INVALID_NOT_CONNECTION,
    //You have to start using the center position
    INVALID_START_NOT_IN_CENTER,
    //Only words of two or more letters
    INVALID_WORD_OF_ONE_LETTER,
    //The new words are not in the dictionary
    INVALID_WORDS_NOT_IN_DICTIONARY,
} CurrentWordResult;
//-----------------------------


/**
* CLASS Board
* Classe que permite guardar el tablero y ir actualizandolo
* Los datos que contiene son:
* Las casillas de este, el dicicionario que se usa, las
* palabras que no estan en el diccionario, la palabra en
* formación la posicion inicial y final de las palabras
* nuevas, las palabras nuevas
*
* Tiene metodos para:
* Poner una ficha en el tablero, comprobar si la palabra actual
* existe en el diccionario, enviar la palabra en formacion a
* palabras ya formadas, eliminar del tablero la palabra en
* formación, comrpobar la alineacion de la palabra, si es
* consecutiva, si tiene conexiones, un buscador de palabras nuevas,
* un ,etodo para calcular los puntos de las palabras formadas,
* un metodo para comprobar las palabras, para concatenar las
* letras de las palabras formadas y un render para imprimir
* el tablero.
 */
class Board
{
public:
    Board(); //{ m_cells; m_dictionary; m_isFirstWord=false; };
    //Board(const string& fitxer);
    ~Board() {};


    PositionResult setTile(Tile& tile, const BoardPosition& boardPos);
    CurrentWordResult checkCurrentWord(int& points);
    void sendCurrentWordToBoard();
    void removeCurrentWord();
    
    int comprovaAlineacio();
    bool comprovaConsecutiu(int tipusAlineacio, int& min, int& max);
    bool comprovaConnexio(int tipusAlineacio, int min, int max);
    bool comprovaConexFitxa(int tipusAlineacio, int fila, int column);
    void buscaParaulesNoves(int tipusAlineacio,int min,int max);
    void buscadorParaules(int tipusAlineacio, int fila, int column);
    int calcularPuntsTotals();
    int calculaPunts(int tipusAlineacio, int identificadorDeParaula, vector<ScoreEffect>& MultiplicadorsDeParaula);
    int tipusPuntuacio(int tipusAlineacio, int fila, int columna, vector<ScoreEffect>& MultiplicadorsDeParaula);
    bool comprobarParaules();
    string concatenarLletres(int tipusAlineacio, int identificadorDeParaula);

    void render(); // Renderiza el tablero con todas las fichas actuales.

    string getWordNotDictionary() const { return m_wordNotInDictionary; }
private:
    const int HORITZONTAL = 1;
    const int VERTICAL = 2;
    Cell m_cells[BOARD_COLS_AND_ROWS][BOARD_COLS_AND_ROWS];
    Dictionary m_dictionary;

    string m_wordNotInDictionary; // Palabra que no esta en el diccionario. (Utilizado en ScrabbleGame.cpp)

    vector<BoardPosition> m_currentWord; //Palabra que se esta formando.
    bool m_isFirstWord; //falso si no esta la primera palabra
    vector<BoardPosition> m_pNovesIn; //primera posició de totes les paraules formades amb cada lletra nova
    vector<BoardPosition> m_pNovesFin; //ultima posició de totes les paraules formades amb cada lletra nova
    vector<string> m_paraules;
    //vector <vector <BoardPosition>> m_paraulesGuardades;
};

#endif /* Board_hpp */
