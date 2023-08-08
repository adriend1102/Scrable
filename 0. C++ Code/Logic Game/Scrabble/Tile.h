//
//  Tile.hpp
//  Scrabble
//

#ifndef Tile_hpp
#define Tile_hpp

/**
* CLASS Tile
* Classe que permite guardar una ficha
* Los datos que contiene son:
* la letra en cuestion y
* su puntuación
*
* Tiene metodos para:
* saber la letra y la puntuación
* y para editar estos atributos
 */
class Tile
{
public:
    Tile() { m_letter = '0'; m_score = 0; }
    Tile(char letter, int score) { m_letter = letter; m_score = score; }
    ~Tile() {}
    char getLetter() const { return m_letter; }
    int getScore() const { return m_score; }
    void setLetter(const char letter) { m_letter = letter; }
    void setScore(const int score) { m_score = score; }
private:
    char m_letter;
    unsigned int m_score;
};


#endif /* Tile_hpp */
