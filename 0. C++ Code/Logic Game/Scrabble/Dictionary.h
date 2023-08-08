//
//  Dictionary.hpp
#pragma once

#include "Scrabble.h"
#include <stdio.h>
#include <iostream>


typedef enum {
    CATALAN = 0,
    SPANISH,
    ENGLISH,
    NO_LANGUAGE
} Language;

/**
* CLASS Dictionary
* Classe que permite guardar el diccionario de un idioma
* Los datos que contiene son:
* las palabras del idioma
* que lenguaje
*
* Tiene metodos para:
* Poner el lenguaje, y saber que lenguaje es el actual, aparte
* saber si una palabra existe en el lenguaje actual
 */
class Dictionary
{
public:
    Dictionary();
    ~Dictionary() {}

    void setLanguage(const Language language);
    Language getCurrentLanguage() const { return m_currentLanguage; }
    bool check(const string& word);

private:
    vector<string> m_words;
    string m_languagesPath[NO_LANGUAGE];
    Language m_currentLanguage;

};
