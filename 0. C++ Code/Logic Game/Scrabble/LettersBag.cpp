//
// LettersBag.cpp
// Scrable
//

#include "LettersBag.h"

/**
* Constructor por defecto,
* coge las letras de la bolsa de un archivo
* dado
 */
LettersBag::LettersBag()
{
	ifstream fitxer;
	fitxer.open("data/Configuration/lettersBag.txt");

	if (fitxer.is_open())
	{
		char letter;
		int score, repetitions;
		// fitxer >> letter >> score >> repetitions;

		while (!fitxer.eof())
		{
			fitxer >> letter >> score >> repetitions;
			Tile newLetter(letter, score);
			for (int i = 0; i < repetitions; i++)
				m_letters.push_back(newLetter);
		}
		fitxer.close();
	}
}


/**
* Metodo que te devuelve una letra
* aelatoria de la bolsa y la elimina
* de esta
 */
Tile LettersBag::getLetter()
{
	srand(time(NULL));
	Tile letter;
	if (m_letters.size() != 0)
	{
		vector<Tile>::iterator aux = m_letters.begin();
		int randomNumber = rand() % m_letters.size();
		aux += randomNumber;
		letter = m_letters[randomNumber];
		m_letters.erase(aux);
	}
	return letter;
}

/**
* Metodo para saber si 
* la bolsa esta vacia
 */
bool LettersBag::isEmpty()
{
	bool res = false;
	if (m_letters.size() == 0)
		res = true;
	return res;
}