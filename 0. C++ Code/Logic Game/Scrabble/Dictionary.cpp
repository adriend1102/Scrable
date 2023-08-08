//
//  Dictionary.cpp


#include "Dictionary.h"

#include <fstream>
#include <string>

using namespace std;

/**
* Constructor por defecto
 */
Dictionary::Dictionary()
{
	// m_currentLanguage = Language::NO_LANGUAGE;

	for (int i = 0; i < 3; i++)
	{
		if (i == Language::ENGLISH)
		{
			m_languagesPath[i] = "data/Dictionaries/English.dic";
		}
		else if (i == Language::SPANISH)
		{
			m_languagesPath[i] = "data/Dictionaries/Spanish.dic";
		}
		else if (i == Language::CATALAN)
		{
			m_languagesPath[i] = "data/Dictionaries/Catalan.dic";
		}
	}

	m_currentLanguage = Language::ENGLISH;
	setLanguage(Language::ENGLISH);
}

// Lee el fichero con la lista de las palabras y las guarda en el atributo m_words.
void Dictionary::setLanguage(const Language language)
{
	ifstream fitxer;
	string pathFitxer = m_languagesPath[language];
	fitxer.open(pathFitxer);

	if (fitxer.is_open())
	{
		string word;
		fitxer >> word;

		while (!fitxer.eof())
		{
			m_words.push_back(word);

			fitxer >> word;
		}
		fitxer.close();
	}

	m_currentLanguage = language;
}

// Comprueba si una palabra existe en el diccionario o no.
bool Dictionary::check(const string& word)
{
	int i = 0;
	bool trobat = false;
	while (!trobat && i < m_words.size())
	{
		if (m_words[i] == word)
		{
			trobat = true;
		}
		else
		{
			i++;
		}
	}
	return trobat;
}