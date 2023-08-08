//
//  ScrabbleGame.cpp
//  Letris
//
//  Created by Enric Vergara on 13/02/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#include <string> 
#include "ScrabbleGame.h"

/**
* Constructor per defecte, inicialitza el joc
*/
ScrabbleGame::ScrabbleGame()
{
	m_lettersBag; //inicializa la bolsa de letras
	vector<Tile> lletres;
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		for (int j = 0; j < MAX_TILES; j++)
			lletres.push_back(m_lettersBag.getLetter());
		m_players[i].inicialitza(lletres); //se aignan 7 fichas a cada jugador
		lletres.clear();
	}
	
	m_currentPlayer = 0;
	m_final = false;
	// Hay que inicializar todos los botones.
	Button buttonPass(IMAGE_NAME::IMAGE_BUTTON_PASS_NORMAL, IMAGE_NAME::IMAGE_BUTTON_PASS_PRESSED, SCREEN_SIZE_X*0.5 - btn_size_w *0.5, SCREEN_SIZE_Y - btn_size_h, btn_size_w, btn_size_h);
	Button buttonRecall(IMAGE_NAME::IMAGE_BUTTON_RECALL_NORMAL, IMAGE_NAME::IMAGE_BUTTON_RECALL_PRESSED, SCREEN_SIZE_X * 0.5 - btn_size_h - btn_size_w *0.5, SCREEN_SIZE_Y - btn_size_h, btn_size_h, btn_size_h);
	Button buttonShuffle(IMAGE_NAME::IMAGE_BUTTON_SHUFFLE_NORMAL, IMAGE_NAME::IMAGE_BUTTON_SHUFFLE_PRESSED, SCREEN_SIZE_X * 0.5 + btn_size_w *0.5, SCREEN_SIZE_Y - btn_size_h, btn_size_h, btn_size_h);
	Button buttonsSend(IMAGE_NAME::IMAGE_BUTTON_SEND_NORMAL, IMAGE_NAME::IMAGE_BUTTON_SEND_PRESSED, SCREEN_SIZE_X * 0.5 - btn_size_w * 0.5, SCREEN_SIZE_Y - btn_size_h, btn_size_w, btn_size_h);

	m_buttonPass = buttonPass;
	m_buttonRecall = buttonRecall;
	m_buttonShuffle = buttonShuffle;
	m_buttonsSend = buttonsSend;
}

/**
* Destructor por defecto.
*/
ScrabbleGame::~ScrabbleGame(){}

/**
* Metodo que imprime en la pantalla los datos actuales
* de la partida, turno del jugador, puntuaciones, fichas
* actuales en la bolsa etc.
*/
void ScrabbleGame::showPlrData()
{
	float posY = SCREEN_SIZE_Y - 95, size = .6;

	GraphicManager::getInstance()->drawFont(FONT_NAME::FONT_WHITE_30, 60, 0, .7, "Player turn: " + to_string(m_currentPlayer + 1));

	for (int i = 0; i < NUM_PLAYERS; i++)
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 0, posY + i * 90 / NUM_PLAYERS, size, "Score Player " + to_string(i + 1) + " = " + to_string(m_players[i].getScore()));

	float posX = SCREEN_SIZE_X - 200;
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posX, posY, size, "Tiles in the bag: " + to_string(m_lettersBag.getNLetters()));
}


/**
* Metodo que imprime en la pantalla los errores de la
* palabra que se forma actualmente (solo se activa cuando hay jugadas)
*/
void ScrabbleGame::showErrMsg(const CurrentWordResult& errMsg, const int points)
{
	string msg = "";
	FONT_NAME fontName = FONT_NAME::FONT_RED_30;

	switch (errMsg)
	{
	case ALL_CORRECT:
		fontName = FONT_NAME::FONT_GREEN_30;
		msg = "Points: " + to_string(points);
		break;
	case INVALID_NOT_ALIGNED:
		msg = "Tiles must be vertically or horizontally aligned and together.";
		break;
	case INVALID_NOT_CONNECTION:
		msg = "At least one letter must be next to the rest of the words.";
		break;
	case INVALID_START_NOT_IN_CENTER:
		msg = "You have to start using the center position.";
		break;
	case INVALID_WORDS_NOT_IN_DICTIONARY:
		msg = "The new words are not in the dictionary: " + m_board.getWordNotDictionary();
		break;
	case INVALID_WORD_OF_ONE_LETTER:
		msg = "Only words of two or more letters.";
		break;
	}

	GraphicManager::getInstance()->drawFont(fontName, 195, 0, .7, msg);
}

/**
* Metodo que imprime en la pantalla el mensaje de fin del juego
* y agradecimientos
*/
void ScrabbleGame::endMsg(Player p[])
{
	string msg = "";
	FONT_NAME fontName = FONT_NAME::FONT_RED_30;
	int i = 0;
	int jugadorGuanyador = 0;
	int puntsMaxims = p[i].getScore();
	while (i < NUM_PLAYERS)
	{
		if (puntsMaxims < p[i].getScore())
		{
			puntsMaxims = p[i].getScore();
			jugadorGuanyador = i;
		}
		else i++;
	}
	std::string s1 = std::to_string(jugadorGuanyador + 1);
	std::string s = std::to_string(puntsMaxims);
	msg = "The Winer is: Player " + s1;
	msg += " With: " + s + " points";
	GraphicManager::getInstance()->drawFont(fontName, 195, 0, .7, msg);

	GraphicManager::getInstance()->drawFont(fontName, SCREEN_SIZE_X / 2 - 90, BOARD_POS_Y + BOARD_SIZE + 10, .8, "Congratulations!!!");

	GraphicManager::getInstance()->drawFont(fontName, SCREEN_SIZE_X / 2 - 110, BOARD_POS_Y + BOARD_SIZE + 30, .8, "Thanks for playing :)");

	GraphicManager::getInstance()->drawFont(fontName, SCREEN_SIZE_X / 2 - 220, BOARD_POS_Y + BOARD_SIZE + 50, .8, "Developed by: Adrian Vargas & Yeray Cordero");
}


/**
* Metodo principal, se encarga de llamar a
* todos los otros metodos y actualizar el
* juego en cada instante
*/
void ScrabbleGame::updateAndRender (int mousePosX, int mousePosY, bool mouseStatus)
{
	GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0); //fondo
	//GraphicManager::getInstance()->drawFont(FONT_NAME::FONT_WHITE_30, 60, 0, .7, "Player turn: " + to_string(m_currentPlayer + 1)); //escribe de quien es el turno

	showPlrData(); //imprime los datos de la partida
	

	m_board.render(); //dibuja el tablero

	m_buttonRecall.render(); //dibuja el boton RECALL

	m_buttonShuffle.render(); //dibuja el boton SHUFFLE

	if (!m_players[m_currentPlayer].getAlgunaJugada())
		m_buttonPass.render(); //si hay alguna jugada dibuja el boton PASS
	else
	{
		m_buttonsSend.render(); // si no hay alguna jugada imprime el boton SEND

		int points = 0;
		CurrentWordResult errMsg = m_board.checkCurrentWord(points);
		showErrMsg(errMsg, points); //imprime los erorres del tablero en cada momento
	}

	if (!m_final) //si no se ha acabado el juego (cuando se acaban las fichas de la bag y un jugador se queda sin fichas)
	{

		m_players[m_currentPlayer].update(mousePosX, mousePosY, mouseStatus, m_board);//actualiza los estados de las fichas de cada jugador y situa las fichas en el tablero

		m_players[m_currentPlayer].render();//dibuja los estados de las fichas (menos las del tablero, eso lo hace el render del board)

		if (m_buttonsSend.update(mousePosX, mousePosY, mouseStatus) == ButtonState::PRESSED && m_players[m_currentPlayer].getAlgunaJugada())
			buttonSend(); //llama al metodo pdel boton SEND
		else if (m_buttonRecall.update(mousePosX, mousePosY, mouseStatus) == ButtonState::PRESSED)
			buttonRecall();//llama al metodo del boton RECALL
		else if (m_buttonShuffle.update(mousePosX, mousePosY, mouseStatus) == ButtonState::PRESSED)
			buttonShuffle();//llama al metodo del boton SHUFFLE
		else if (m_buttonPass.update(mousePosX, mousePosY, mouseStatus) == ButtonState::PRESSED && !m_players[m_currentPlayer].getAlgunaJugada())
			buttonPass();
	}
	else
		endMsg(m_players); //si la partida acaba imprime el mensaje del final

	
}

/**
* Activa las funciones del boton SEND:
* Si la palabra en formacin es correcta
*	la envia al tablero, y act la puntuacion del jugador actual
*	y le reparte nuevas fichas hasta tener 7 en total
*	ademas comprueba si la bolsa esta vacia para saber
*	si el juego se acaba
*/
void ScrabbleGame::buttonSend()
{
	CurrentWordResult res = CurrentWordResult::INVALID_START_NOT_IN_CENTER;
	int points = 0;

	res = m_board.checkCurrentWord(points);
	if (res == CurrentWordResult::ALL_CORRECT)
	{
		m_board.sendCurrentWordToBoard();//envia al tablero
		m_players[m_currentPlayer].setScore(m_players[m_currentPlayer].getScore() + points);
		for (int i = 0; i < MAX_TILES; i++)
		{
			if (m_players[m_currentPlayer].getPlayerTile(i).getOnBoard())
			{
				Tile t = m_lettersBag.getLetter();
				m_players[m_currentPlayer].rellenar(t, i);//reparte las fichas (llama al metodo rellenar
			}
		}
		m_players[m_currentPlayer].setAlgunaJugada(false);//actualiza el estado poniendo que no hay ninguna jugada

		if (m_lettersBag.isEmpty())//si la bolsa esta vacia
		{
			int i = 0;
			m_final = true;
			while (i < MAX_TILES && m_final)
			{
				if (m_players[m_currentPlayer].getPlayerTile(i).getTile().getLetter() != '0')//comprueba si el jugador se ha quedado sin fichas
					m_final = false;
				else
					i++;
			}
		}
	}
}


/**
* Activa las funciones del boton RECALL:
* Llama al metodo recall de la clase playerTile para 
*	posicionar las fichas en su posicion inicial
* */
void ScrabbleGame::buttonRecall()
{
	m_board.removeCurrentWord();
	for (int i = 0; i < MAX_TILES; i++)
		m_players[m_currentPlayer].recall(i);
}


/**
* Activa las funciones del boton SHUFFLE:
* Llama al metodo recall de la clase playerTile
*	para devolver las fichas a su posicion inicial
*	y luego llama al metodo shuffle que reordena aleatoriamente las fichas del jugador actual
*/
void ScrabbleGame::buttonShuffle()
{
	m_board.removeCurrentWord();
	for (int i = 0; i < MAX_TILES; i++)
		m_players[m_currentPlayer].recall(i);
	m_players[m_currentPlayer].shuffle();
}

/**
* Activa las funciones del boton PASS:
* Pasa al siguiente jugador
*/
void ScrabbleGame::buttonPass()
{
	if (m_currentPlayer < (NUM_PLAYERS - 1))
		m_currentPlayer++;
	else
		m_currentPlayer = 0;
}

//apartir de aqui todo son comentarios de codigo de prueba que estaba mal (otras verisones)


//Adri

/*else
{
	m_board.removeCurrentWord();
	for (int i = 0; i < MAX_TILES; i++)
		m_players[m_currentPlayer].recall(i);
}*/
// Eliminar fichas jugadas del jugador actual y darle nuevas fichas del getLetter() de LettersBag para que tenga 7 fichas.
/*if (m_currentPlayer < (NUM_PLAYERS - 1))
				m_currentPlayer++;
			else
				m_currentPlayer = 0;*/
//int i = 0;
	/*while (i < MAX_TILES)
	{
		Tile t= m_players[m_currentPlayer].getPlayerTile(i).getTile();
		BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(i).getBoardPosition();
		if (m_board.setTile(t, bp) == PositionResult::VALID_POSITION)
		{
			//BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(i).getBoardPosition();
			//m_board.setTile(t, bp);
			m_players[m_currentPlayer].setInBoard(i, true);
		}
		else if (m_board.setTile(t, bp) == PositionResult::INVALID_POSITION && !m_players[m_currentPlayer].getMoviment())
		{
			m_players[m_currentPlayer].recall(i);
			m_players[m_currentPlayer].setInBoard(i, false);
		}
		else if (m_players[m_currentPlayer].getInBoard(i) && !m_players[m_currentPlayer].getPlayerTile(i).getOnBoard())
		{
			m_board.removeCurrentWord();
			m_players[m_currentPlayer].setInBoard(i, false);
			for (int j = 0; j < MAX_TILES; j++)
			{
				if (m_players[m_currentPlayer].getInBoard(j) && m_players[m_currentPlayer].getPlayerTile(j).getOnBoard())
				{
					BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(j).getBoardPosition();
					Tile t = m_players[m_currentPlayer].getPlayerTile(j).getTile();
					m_board.setTile(t, bp);
				}
			}
		}
		i++;
	}*/
	/*while (i < MAX_TILES)
	{
		Tile t = m_players[m_currentPlayer].getPlayerTile(i).getTile();
		BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(i).getBoardPosition();
		if (m_board.setTile(t, bp) == PositionResult::VALID_POSITION)
		{
			//BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(i).getBoardPosition();
			//m_board.setTile(t, bp);
			m_players[m_currentPlayer].setInBoard(i, true);
		}
		else if (m_board.setTile(t, bp) == PositionResult::INVALID_POSITION && !m_players[m_currentPlayer].getMoviment())
		{
			m_players[m_currentPlayer].recall(i);
			m_players[m_currentPlayer].setInBoard(i, false);
		}
		else if (m_board.setTile(t, bp) == PositionResult::NOT_EMPTY && !m_players[m_currentPlayer].getMoviment() && !m_players[m_currentPlayer].getInBoard(i))
		{
			m_players[m_currentPlayer].recall(i);
			m_players[m_currentPlayer].setInBoard(i, false);
			BoardPosition bp(-1,-1);
			m_players[m_currentPlayer].getPlayerTile(i).setBoardPosition(bp);
		}
		else if (m_players[m_currentPlayer].getInBoard(i) && !m_players[m_currentPlayer].getPlayerTile(i).getOnBoard() && mouseStatus && m_players[m_currentPlayer].getMoviment())
		{
			m_board.removeCurrentWord();
			m_players[m_currentPlayer].setInBoard(i, false);
			m_players[m_currentPlayer].toMove(i);
			for (int j = 0; j < MAX_TILES; j++)
			{
				if (m_players[m_currentPlayer].getInBoard(j) && m_players[m_currentPlayer].getPlayerTile(j).getOnBoard())
				{
					BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(j).getBoardPosition();
					Tile t = m_players[m_currentPlayer].getPlayerTile(j).getTile();
					m_board.setTile(t, bp);
				}
			}
		}
		i++;
	}*/
	/*else if (m_players[m_currentPlayer].getInBoard(i) && !m_players[m_currentPlayer].getPlayerTile(i).getOnBoard() && mouseStatus && m_players[m_currentPlayer].getMoviment())
	{
		m_board.removeCurrentWord();
		m_players[m_currentPlayer].setInBoard(i, false);
		/*for (int j = 0; j < MAX_TILES; j++)
		{
			if (m_players[m_currentPlayer].getInBoard(j) && m_players[m_currentPlayer].getPlayerTile(j).getOnBoard())
			{
				BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(j).getBoardPosition();
				Tile t = m_players[m_currentPlayer].getPlayerTile(j).getTile();
				m_board.setTile(t, bp);
			}
		}
	}*/


	/*else if (m_board.setTile(t, m_players[m_currentPlayer].getPlayerTile(i).getBoardPosition()) == NOT_EMPTY && m_players[m_currentPlayer].getInBoard(i))
	{
		BoardPosition bp;
		bp.setCol(-1);
		bp.setRow(-1);
		m_players[m_currentPlayer].recall(i);
		m_board.removeCurrentWord();
		m_players[m_currentPlayer].setInBoard(i, false);
		m_players[m_currentPlayer].getPlayerTile(i).setBoardPosition(bp);
		for (int j = 0; j < MAX_TILES; j++)
		{
			if (m_players[m_currentPlayer].getInBoard(j) && m_players[m_currentPlayer].getPlayerTile(j).getOnBoard())
			{
				BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(j).getBoardPosition();
				Tile t = m_players[m_currentPlayer].getPlayerTile(j).getTile();
				m_board.setTile(t, bp);
			}
		}
	}*/
	/*for (int j = 0; j < MAX_TILES; j++)
	{
		if (m_players[m_currentPlayer].getInBoard(j) && m_players[m_currentPlayer].getPlayerTile(j).getOnBoard())
		{
			BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(j).getBoardPosition();
			Tile t = m_players[m_currentPlayer].getPlayerTile(j).getTile();
			m_board.setTile(t, bp);
		}
	}
	m_players[m_currentPlayer].getPlayerTile(i).setEmpty(false);
	m_players[m_currentPlayer].getPlayerTile(i).setOnBoard(false);
	m_players[m_currentPlayer].getPlayerTile(i).setPos(m_players[m_currentPlayer].getPosIniciX(i), POS_Y);
}*/
//Tile t;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//Yeray:


// GraphicManager::getInstance()->drawFont(FONT_NAME::FONT_WHITE_30, 0, SCREEN_SIZE_Y - 100, .7, "Score Player: " + to_string(m_currentPlayer + 1) + " = " + to_string(m_players[0].getScore()));

/*Tile t;
	t.setLetter('b');
	BoardPosition bp;
	bp.setCol(2);
	bp.setRow(4);
	m_board.setTile(t, bp);
	m_board.render();*/


	// LO DE AQUÍ DEBAJO NO SIRVE PARA NADA -> BORRAR

	/*
	GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0);

	GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, BOARD_POS_X, BOARD_POS_Y);

	int posX = BOARD_POS_X;
	int posY = BOARD_POS_Y;
	for (int i = 0; i < BOARD_COLS_AND_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS_AND_ROWS; j++)
		{
			GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_A_SMALL, posX, posY);
			posX += BOARD_TILE_SIZE
			;
		}
		posY += BOARD_TILE_SIZE;
		posX = BOARD_POS_X;
	}

	if (mouseStatus)
	{
		int posX = BOARD_POS_X;
		int posY = BOARD_POS_Y;
		if (mousePosX > BOARD_POS_X && mousePosX < (BOARD_POS_X + BOARD_SIZE) && mousePosY > BOARD_POS_Y && mousePosY < (BOARD_POS_Y + BOARD_SIZE))
		{
			for (int i = 0; i < BOARD_COLS_AND_ROWS; i++)
			{
				for (int j = 0; j < BOARD_COLS_AND_ROWS; j++)
				{
					GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_A_SMALL, posX, posY);
					posX += BOARD_TILE_SIZE;
				}
				posY += BOARD_TILE_SIZE;
				posX = BOARD_POS_X;
			}
		}
	}

	std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 10, 10, 0.6, msg);
	*/