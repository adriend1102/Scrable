//
//  Board.cpp
//  Scrabble
//

#include "Board.h"
#include <algorithm>
#include <iostream>
#include <fstream>
/**
* Constructor por defecto, que inicializa
* los multiplicadores desde un fichero
 */
Board::Board()
{
	m_isFirstWord = false;
	ifstream f;
	f.open("data/Configuration/Board.txt");
	if (f.is_open())
	{
		int fila;
		int column;
		string x;
		ScoreEffect s;
		f >> fila >> column >> x;

		while (!f.eof())
		{
			if (x == "DL")
				s = ScoreEffect::DL;
			else if (x == "TL")
				s = ScoreEffect::TL;
			else if (x == "DW")
				s = ScoreEffect::DW;
			else if (x == "TW")
				s = ScoreEffect::TW;
			else
				s = ScoreEffect::NO_EFFECT;

			m_cells[fila][column].setScoreEffect(s);
			f >> fila >> column >> x;

		}
		f.close();
	}
}

// m_tilePlayed = false si la ficha todavia se sigue jugando y true si ya se ha construido la palabra.
/**
* Metodo para poner una ficha al tablero
 */
PositionResult Board::setTile(Tile& tile, const BoardPosition& boardPos)
{
	PositionResult resultat = PositionResult::INVALID_POSITION;

	if (boardPos.getRow() >= 0 && boardPos.getCol() >= 0 && boardPos.getRow() <= BOARD_COLS_AND_ROWS && boardPos.getCol() <= BOARD_COLS_AND_ROWS)
	{
		if (m_cells[boardPos.getRow()][boardPos.getCol()].getEmpty() == true)
		{
			resultat = PositionResult::VALID_POSITION;
			m_cells[boardPos.getRow()][boardPos.getCol()].setEmpty(false);
			m_cells[boardPos.getRow()][boardPos.getCol()].setTilePlayed(false);
			m_cells[boardPos.getRow()][boardPos.getCol()].setTile(tile);
			m_currentWord.push_back(boardPos);
		}
		else
		{
			resultat = PositionResult::NOT_EMPTY;
		}
	}

	return resultat;
}

/**
* Metodo para eliminar la palabra en formación
* del tablero
 */
void Board::removeCurrentWord()
{
	for (int i = 0; i < m_currentWord.size(); i++)
	{
		int col = m_currentWord[i].getCol();
		int row = m_currentWord[i].getRow();
		m_cells[row][col].setEmpty(true);
	}

	m_currentWord.clear();
}
/**
* Metodo para fijar en el tablero
* la palabra en formación
 */
void Board::sendCurrentWordToBoard()
{
	for (int i = 0; i < m_currentWord.size(); i++)
	{
		int col = m_currentWord[i].getCol();
		int row = m_currentWord[i].getRow();
		m_cells[row][col].setTilePlayed(true);
	}
	m_currentWord.clear();
	m_isFirstWord = true;////////////////
	//m_oWordFinder.resetTotalScore();
}

/**
* Metodo para comprobar la alinacion
* de la palabra en formación, 0 si no esta
* alineada, 1 si es horizontal 2 si es 
* vertical
 */
int Board::comprovaAlineacio()
{
	//int i = 1;
	bool cond = false;
	int ret = 0;
	if (m_currentWord.size() <= 1)
		ret = 1;
	else if (m_currentWord.size() > 1)
	{
		if (m_currentWord[0].getRow() == m_currentWord[1].getRow())
		{
			int i = 1;
			while (i < m_currentWord.size() - 1 && !cond)
			{
				if (m_currentWord[i].getRow() == m_currentWord[i + 1].getRow())//i + 1
					i++;
				else
					cond = true;
			}
			ret = HORITZONTAL;
		}
		else if (m_currentWord[0].getCol() == m_currentWord[1].getCol())
		{
			int i = 1;
			while (i < m_currentWord.size() - 1 && !cond)
			{
				if (m_currentWord[i].getCol() == m_currentWord[i + 1].getCol())//i + 1
					i++;
				else
					cond = true;
			}
			ret = VERTICAL;
		}
		if (cond)
			ret = 0;
	}
	return ret;
}

/**
* Metodo para comprobar si la palabra es consecutiva
 */
bool Board::comprovaConsecutiu(int tipusAlineacio, int& min, int& max)
{
	bool ret=true;
	int i = 0;
	switch (tipusAlineacio)
	{
	case 1:
		min = m_currentWord[0].getCol();
		max = m_currentWord[0].getCol();
		for (i = 0; i < m_currentWord.size(); i++)
		{
			if (m_currentWord[i].getCol() < min)
				min = m_currentWord[i].getCol();
			else if(m_currentWord[i].getCol() > max)
				max = m_currentWord[i].getCol();
		}
		i = min;
		while (ret && i <= max)
		{
			if (m_cells[m_currentWord[0].getRow()][i].getEmpty())
				ret = false;
			else
				i++;
		}
		break;
	case 2:
		min = m_currentWord[0].getRow();
		max = m_currentWord[0].getRow();
		for (i = 0; i < m_currentWord.size(); i++)
		{
			if (m_currentWord[i].getRow() < min)
				min = m_currentWord[i].getRow();
			else if (m_currentWord[i].getRow() > max)
				max = m_currentWord[i].getRow();
		}
		i = min;
		while (ret && i <= max)
		{
			if (m_cells[i][m_currentWord[0].getCol()].getEmpty())
				ret = false;
			else
				i++;
		}
		break;
	default:
		ret = false;
		break;
	}
	
	return ret;
}

/**
* Metodo para comprobar si la palabra tiene conexiones
 */
bool Board::comprovaConnexio(int tipusAlineacio, int min, int max)
{
	int i = min;
	bool conect = false;

	switch (tipusAlineacio)
	{
	case 1:
		if (0 < min)
			conect = m_cells[m_currentWord[0].getRow()][min - 1].getTilePlayed();
		while (!conect && i <= max)
		{
			conect = comprovaConexFitxa(tipusAlineacio, m_currentWord[0].getRow(), i);
			i++;
		}
		if (BOARD_COLS_AND_ROWS - 1 > max && !conect)
			conect = m_cells[m_currentWord[0].getRow()][max + 1].getTilePlayed();
		break;
	case 2:
		if (0 < min)
			conect = m_cells[min - 1][m_currentWord[0].getCol()].getTilePlayed();	
		while (!conect && i <= max)
		{
			conect = comprovaConexFitxa(tipusAlineacio, i, m_currentWord[0].getCol());
			i++;

		}
		if (BOARD_COLS_AND_ROWS - 1 > max && !conect)
			conect = m_cells[max + 1][m_currentWord[0].getCol()].getTilePlayed();
		break;
	default:
		break;
	}
	return conect;
}

/**
* Submetodo para comprobar si cada ficha
* tiene conexiones, esto nos permite hacer
* menos comparaciones (solo arriba y abajo
* si la alineacion es horizontal y izquierda
* y derecha en caso contrario)
 */
bool Board::comprovaConexFitxa(int tipusAlineacio, int fila, int column)
{
	bool conect = false;

	switch (tipusAlineacio)
	{
	case 1:
		conect = m_cells[fila][column].getTilePlayed();
		if (!conect)
		{
			if (0 < fila && !conect)
				conect = m_cells[fila - 1][column].getTilePlayed();
			if (BOARD_COLS_AND_ROWS - 1 > fila && !conect)
				conect = m_cells[fila + 1][column].getTilePlayed();
		}
		break;
	case 2:
		conect = m_cells[fila][column].getTilePlayed();
		if (!conect)
		{
			if (0 < column && !conect)
				conect = m_cells[fila][column - 1].getTilePlayed();
			if (BOARD_COLS_AND_ROWS - 1 > column && !conect)
				conect = m_cells[fila][column + 1].getTilePlayed();
		}
		break;
	default:
		break;
	}
	return conect;
}


/**
* Metodo para buscar palabras nuevas
* (llama a un submetodo) la primera
letra aparte de buscar las
* palabras en la direccion del resto
* tambien las busca en la direccion
* perpendicular, esto para ahorrar
* comparaciones extra
 */
void Board::buscaParaulesNoves(int tipusAlineacio, int min, int max)
{
	int i;
	switch (tipusAlineacio)
	{
	case 1:
		buscadorParaules(VERTICAL, m_currentWord[0].getRow(), min);
		for (i = min; i <= max; i++)
			buscadorParaules(tipusAlineacio, m_currentWord[0].getRow(), i);
		break;
	case 2:
		buscadorParaules(HORITZONTAL, min, m_currentWord[0].getCol());
		for (i = min; i <= max; i++)
			buscadorParaules(tipusAlineacio, i, m_currentWord[0].getCol());
		break;
	default:
		break;
	}
}

/**
* Submetodo para buscar palabras nuevas,
* comprueba cada casilla y la va guardando
* hasta que encuentra una casilla vacia,
* guarda la primera y la ultima casilla de las
* nuevas palabras formadas, y si coinciden, se
* se eliminan del registro, ya que eso significa
* que no es una palabra nueva sino solo una letra nueva
*/
void Board::buscadorParaules(int tipusAlineacio, int fila, int column)
{
	m_pNovesIn.push_back(BoardPosition(column, fila));
	m_pNovesFin.push_back(BoardPosition(column, fila));
	int j;
	bool cond = false;
	switch (tipusAlineacio)
	{
	case 1:
		j = fila;
		if (!m_cells[fila][column].getTilePlayed())
		{
			while (j >= 0 && !cond)
			{
				if (!m_cells[j][column].getEmpty())
				{
					m_pNovesIn[m_pNovesIn.size() - 1].setRow(j);
					j--;
				}
				else
					cond = true;
			}
			j = m_currentWord[0].getRow();
			cond = false;
			while (j <= BOARD_COLS_AND_ROWS - 1 && !cond)
			{
				if (!m_cells[j][column].getEmpty())
				{
					m_pNovesFin[m_pNovesFin.size() - 1].setRow(j);
					j++;
				}
				else
					cond = true;
			}
		}
		break;
	case 2:
		j = column;
		if (!m_cells[fila][column].getTilePlayed())
		{
			while (j >= 0 && !cond)
			{
				if (!m_cells[fila][j].getEmpty())
				{
					m_pNovesIn[m_pNovesIn.size() - 1].setCol(j);
					j--;
				}
				else
					cond = true;
			}
			j = m_currentWord[0].getCol();
			cond = false;
			while (j <= BOARD_COLS_AND_ROWS - 1 && !cond)
			{
				if (!m_cells[fila][j].getEmpty())
				{
					m_pNovesFin[m_pNovesFin.size() - 1].setCol(j);
					j++;
				}
				else
					cond = true;
			}
		}
		break;
	default:
		break;
	}
	if (m_pNovesFin[m_pNovesFin.size() - 1] == m_pNovesIn[m_pNovesIn.size() - 1])
	{
		m_pNovesFin.pop_back();
		m_pNovesIn.pop_back();
	}
}

/**
* Metodo para calcular los puntos totales
* llama a un submetodo.
*/
int Board::calcularPuntsTotals()
{
	int puntuacioT = 0;
	vector<ScoreEffect> MultiplicadorsDeParaula;
	if (m_pNovesFin.size() != 0)
	{
		for (int i = 0; i < m_pNovesFin.size(); i++)
		{
			if (m_pNovesFin[i].getRow() == m_pNovesIn[i].getRow())
				puntuacioT += calculaPunts(HORITZONTAL, i, MultiplicadorsDeParaula);
			else if (m_pNovesFin[i].getCol() == m_pNovesIn[i].getCol())
				puntuacioT += calculaPunts(VERTICAL, i, MultiplicadorsDeParaula);
		}
	}
	return puntuacioT;
}

/**
* Submetodo para calcular los puntos de cada
* palabra, llama a un subsubmetodo para guardar
* los puntos de cada palabra y si hay multiplicadores
*/
int Board::calculaPunts(int tipusAlineacio, int identificadorDeParaula, vector<ScoreEffect>& MultiplicadorsDeParaula)
{
	int fila;
	int columna;
	int puntuacio = 0;
	switch (tipusAlineacio)
	{
	case 1:
		fila= m_pNovesFin[identificadorDeParaula].getRow();
		for (columna = m_pNovesIn[identificadorDeParaula].getCol(); columna <= m_pNovesFin[identificadorDeParaula].getCol(); columna++)
			puntuacio += tipusPuntuacio(tipusAlineacio, fila, columna, MultiplicadorsDeParaula);
		break;
	case 2:
		columna = m_pNovesFin[identificadorDeParaula].getCol();
		for (fila = m_pNovesIn[identificadorDeParaula].getRow(); fila <= m_pNovesFin[identificadorDeParaula].getRow(); fila++)
			puntuacio += tipusPuntuacio(tipusAlineacio, fila, columna, MultiplicadorsDeParaula);
		break;
	default:
		break;
	}
	for (int i = 0; i < MultiplicadorsDeParaula.size(); i++)
	{
		if (MultiplicadorsDeParaula[i] == ScoreEffect::DW)
			puntuacio *= 2;
		else	if (MultiplicadorsDeParaula[i] == ScoreEffect::TW)
			puntuacio *= 3;
	}
	MultiplicadorsDeParaula.clear();
	return puntuacio;
}

/**
* Susubbmetodo para aplicar los multiplicadores
* y calcular la puntuacion final de cada
* palabra
*/
int Board::tipusPuntuacio(int tipusAlineacio, int fila, int columna, vector<ScoreEffect>& MultiplicadorsDeParaula)
{
	int puntuacio = 0;
	if (!m_cells[fila][columna].getTilePlayed() && m_cells[fila][columna].getScoreEffect() != ScoreEffect::NO_EFFECT)
	{
		if (m_cells[fila][columna].getScoreEffect() == ScoreEffect::DL)
			puntuacio = (m_cells[fila][columna].getTile().getScore() * 2);
		else if (m_cells[fila][columna].getScoreEffect() == ScoreEffect::TL)
			puntuacio = (m_cells[fila][columna].getTile().getScore() * 3);
		else
		{
			MultiplicadorsDeParaula.push_back(m_cells[fila][columna].getScoreEffect());
			puntuacio = (m_cells[fila][columna].getTile().getScore());
		}
	}
	else
		puntuacio = m_cells[fila][columna].getTile().getScore();
	return puntuacio;
}

/**
* Metodo para comprobar si una palabra existe
* en el diccionario seleciconado
*/
bool Board::comprobarParaules()
{
	bool ret = true;
	int i = 0;
	while ( i < m_pNovesFin.size() && ret)
	{
		if (m_pNovesFin[i].getRow() == m_pNovesIn[i].getRow())
			m_paraules.push_back(concatenarLletres(HORITZONTAL, i));// += calculaPunts(HORITZONTAL, i, MultiplicadorsDeParaula);
		else if (m_pNovesFin[i].getCol() == m_pNovesIn[i].getCol())
			m_paraules.push_back(concatenarLletres(VERTICAL, i));
		ret = m_dictionary.check(m_paraules[i]);
		if (ret == false)
			m_wordNotInDictionary = m_paraules[i];
		i++;
	}
	return ret;

}

/**
* Metodo para concatenar las letras de las
* palabras nuevas para luego poderlas guardar
*/
string Board::concatenarLletres(int tipusAlineacio, int identificadorDeParaula)
{
	int fila;
	int columna;
	string paraula;
	switch (tipusAlineacio)
	{
	case 1:
		fila = m_pNovesFin[identificadorDeParaula].getRow();
		for (columna = m_pNovesIn[identificadorDeParaula].getCol(); columna <= m_pNovesFin[identificadorDeParaula].getCol(); columna++)
			paraula = paraula + m_cells[fila][columna].getTile().getLetter();
		break;
	case 2:
		columna = m_pNovesFin[identificadorDeParaula].getCol();
		for (fila = m_pNovesIn[identificadorDeParaula].getRow(); fila <= m_pNovesFin[identificadorDeParaula].getRow(); fila++)
			paraula = paraula + m_cells[fila][columna].getTile().getLetter();
		break;
	default:
		break;
	}
	return paraula;
}



/**
* Metodo que llama a todos los
* metodos anteriores para saber
* los estados del tablero
*/
CurrentWordResult Board::checkCurrentWord(int& points)
{
	CurrentWordResult ret;
	int min = 0;
	int max = 0;
	bool conexio = false;
	int tipusAlineacio = comprovaAlineacio();
	bool consecutiu = comprovaConsecutiu(tipusAlineacio, min, max);
	if (m_currentWord.size() == 1)
	{
		while (!conexio && tipusAlineacio <= 2) //comprueba en vertical y horizontal si hay una ficha
		{
			conexio = comprovaConnexio(tipusAlineacio, min, max);
			if (conexio == false)
			{
				tipusAlineacio++;
				min = m_currentWord[0].getRow();
				max = m_currentWord[0].getRow();
			}
		}
	}
	else
		conexio = comprovaConnexio(tipusAlineacio, min, max);
	if (tipusAlineacio == 0 || !consecutiu)
		ret = CurrentWordResult::INVALID_NOT_ALIGNED;
	else if (!m_isFirstWord && m_cells[(BOARD_COLS_AND_ROWS - 1) / 2][(BOARD_COLS_AND_ROWS - 1) / 2].getEmpty())
		ret = CurrentWordResult::INVALID_START_NOT_IN_CENTER;
	else if (m_currentWord.size() == 1 && !conexio)
		ret = CurrentWordResult::INVALID_WORD_OF_ONE_LETTER;
	else if (tipusAlineacio != 0)
	{
		//conexio = comprovaConnexio(tipusAlineacio, min, max);
		if (conexio || !m_isFirstWord && !m_cells[(BOARD_COLS_AND_ROWS - 1) / 2][(BOARD_COLS_AND_ROWS - 1) / 2].getEmpty())
		{
			buscaParaulesNoves(tipusAlineacio, min, max);
			
				if (comprobarParaules())
				{
					points = calcularPuntsTotals();
					ret = CurrentWordResult::ALL_CORRECT;
				}
				else
					ret = CurrentWordResult::INVALID_WORDS_NOT_IN_DICTIONARY;
		}
		else
			ret = CurrentWordResult::INVALID_NOT_CONNECTION;
	}
	m_pNovesFin.clear();
	m_pNovesIn.clear();
	m_paraules.clear();
	return ret;
}

/**
* Metodo para imprimir el estado del tablero
*/
void Board::render()
{
	GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, BOARD_POS_X, BOARD_POS_Y);

	float posX = BOARD_POS_X;
	float posY = BOARD_POS_Y;
	for (int i = 0; i < BOARD_COLS_AND_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS_AND_ROWS; j++)
		{
			m_cells[i][j].render(posX, posY);
			posX += BOARD_TILE_SIZE;
		}
		posY += BOARD_TILE_SIZE;
		posX = BOARD_POS_X;
	}
}