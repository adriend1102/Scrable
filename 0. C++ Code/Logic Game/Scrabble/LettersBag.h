// 
// LettersBag.hpp
// Scrable
//

#pragma once

#include <vector>
#include <time.h>
#include <fstream>
#include "Tile.h"

using namespace std;

/**
* CLASS LettersBag
* Classe que permite guardar la bolsa con palabras
* Los datos que contiene son:
* un vector con dicha bolsa
*
* Tiene metodos para:
* coger una letra aleatoria de la bolsa, saber el
* numero de letras que quedan, y saber si la bolsa
* esta vacia
 */
class LettersBag
{
public:
	LettersBag();
	~LettersBag() {};
	Tile getLetter();
	int getNLetters() { return m_letters.size(); }
	bool isEmpty();
private:
	vector<Tile> m_letters;
};