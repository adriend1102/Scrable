#include "Player.h"

/**
* Metodo para inicializar la partida
* asigna las fichas al jugador
*/
void Player::inicialitza(vector<Tile>& fitxes)
{
	m_score = 0;
	//float posX = 0;
	for (int i = 0; i < MAX_TILES; i++)
		m_tiles[i].setTile(fitxes[i]);
}

/**
* Constructor por defecto, inicializa la puntuación
* a 0, las posiciones iniciales de las fichas, y que no hay
* jugadas en proceso
*/
Player::Player()
{
	m_score = 0;
	float posX = (SCREEN_SIZE_X - (btn_size_h * MAX_TILES)) / 8;
	for (int i = 0; i < MAX_TILES; i++)
	{
		m_tiles[i].setPos(posX, POS_Y);
		m_posInicalsX[i] = m_tiles[i].getX();
		posX += (btn_size_h + (SCREEN_SIZE_X - (btn_size_h * MAX_TILES))/8);
	}
	m_algunaJugada = false;
}

/**
* meetodo que cambia 
* el estado de una ficha i
* a "en movimiento"
*/
void Player::toMove(int i)
{
	m_tiles[i].setEmpty(true);
	m_tiles[i].setOnBoard(false);
	m_moviment = true;
	BoardPosition bp(-1, -1);
	m_tiles[i].setBoardPosition(bp);
	algunaJugada();
}

/**
* Metodo que comprueba
* si hay alguna jugada
*/
void Player::algunaJugada()
{
	int j = 0;
	while (!m_algunaJugada && j < MAX_TILES)
	{
		if (m_tiles[j].getOnBoard())
			m_algunaJugada = true;
		j++;
	}
}

/**
* Metodo que pasa una ficha i al tablero
*/
void Player::actAlTauler(float mousePosX, float mousePosY, bool mouseIsPressed, Board& board, int i)
{
	int columna = (mousePosX - BOARD_POS_X) / BOARD_TILE_SIZE;
	int fila = (mousePosY - BOARD_POS_Y) / BOARD_TILE_SIZE;
	BoardPosition bp(columna, fila);
	m_tiles[i].setBoardPosition(bp);
	float posX = columna * BOARD_TILE_SIZE + BOARD_POS_X;
	float posY = fila * BOARD_TILE_SIZE + BOARD_POS_Y;
	m_tiles[i].setPos(posX, posY);
	m_tiles[i].setEmpty(true);
	m_moviment = false;
	//m_tiles[i].setOnBoard(true);
	//m_algunaJugada = true;
	Tile t = m_tiles[i].getTile();
	if (board.setTile(t, bp) == PositionResult::VALID_POSITION)
		m_tiles[i].setOnBoard(true);
	else if (board.setTile(t, bp) == PositionResult::INVALID_POSITION && !m_moviment)
		recall(i);
	else if (board.setTile(t, bp) == PositionResult::NOT_EMPTY && !m_moviment && !m_tiles[i].getOnBoard())
		recall(i);
	else if (m_tiles[i].getOnBoard() && mouseIsPressed &&
		mousePosX > m_tiles[i].getX() && mousePosY > m_tiles[i].getY() &&
		mousePosX < m_tiles[i].getX() + BOARD_TILE_SIZE &&
		mousePosY < m_tiles[i].getY() + BOARD_TILE_SIZE)
	{
		board.removeCurrentWord();
		m_tiles[i].setOnBoard(false);
		toMove(i);
		for (int j = 0; j < MAX_TILES; j++)
		{
			if (m_tiles[j].getOnBoard())
			{
				BoardPosition bp = m_tiles[j].getBoardPosition();
				Tile t = m_tiles[j].getTile();
				board.setTile(t, bp);
			}
		}
	}
}

/**
* Metodo que actualiza el estado de
* las fichas de cada jugador
*/
void Player::update(float mousePosX, float mousePosY, bool mouseIsPressed, Board& board)
{
	for (int i = 0; i < MAX_TILES; i++)
	{
		if (mouseIsPressed && !m_tiles[i].getEmpty() &&
			mousePosX >= m_posInicalsX[i] &&
			mousePosY >= POS_Y &&
			mousePosX <= m_posInicalsX[i] + btn_size_h &&
			mousePosY <= POS_Y + btn_size_h && !m_moviment &&
			m_tiles[i].getTile().getLetter() != '0') // si la letra es 0 (vacia) no se va a mover, esto para no generar posibles errores
		{
			m_tiles[i].setEmpty(true);
			m_tiles[i].setOnBoard(false);
			m_moviment = true;
		}
		else if (m_moviment && mouseIsPressed && m_tiles[i].getEmpty() && !m_tiles[i].getOnBoard())
		{
			m_tiles[i].setEmpty(true);
			m_tiles[i].setOnBoard(false);
			m_tiles[i].setPos(mousePosX, mousePosY);
		}
		else if (!mouseIsPressed && m_tiles[i].getEmpty() && m_moviment && !m_tiles[i].getOnBoard())
		{
			if (mousePosX < BOARD_POS_X ||
				mousePosY < BOARD_POS_Y ||
				mousePosX > BOARD_POS_X + BOARD_SIZE ||
				mousePosY > BOARD_POS_Y + BOARD_SIZE)
			{
				BoardPosition bp(-1, -1);
				m_tiles[i].setBoardPosition(bp);
				recall(i);
			}
			else
				actAlTauler(mousePosX, mousePosY, mouseIsPressed, board, i);
		}
		else if (m_tiles[i].getOnBoard() && mouseIsPressed
			&& mousePosX > m_tiles[i].getX() && mousePosY > m_tiles[i].getY()
			&& mousePosX < m_tiles[i].getX() + BOARD_TILE_SIZE && mousePosY < m_tiles[i].getY() + BOARD_TILE_SIZE &&
			!m_moviment)
			{
				m_algunaJugada = false;
				toMove(i);
				board.removeCurrentWord();
				for (int j = 0; j < MAX_TILES; j++)
				{
					if (m_tiles[j].getOnBoard())
					{
						BoardPosition bp = m_tiles[j].getBoardPosition();
						Tile t = m_tiles[j].getTile();
						board.setTile(t, bp);
					}
				}
			}
	}
	algunaJugada();
}

/**
* Metodo que imprime las fichas en
* la "mano" del jugador y en movimiento
*/
void Player::render()
{
	char letter;
	float posX, posY;
	for (int i = 0; i < MAX_TILES; i++)
	{
		
		if (!m_tiles[i].getEmpty())
		{
			posX = m_tiles[i].getX();
			posY = m_tiles[i].getY();
			letter = m_tiles[i].getTile().getLetter();
			renderTileStatic(posX, posY, letter);
		}
	}
	if (m_moviment)
	{
		int i = 0;
		bool cond = false;
		while (i < MAX_TILES && !cond)
		{
			if (m_tiles[i].getEmpty() && !m_tiles[i].getOnBoard())
				cond = true;
			else
				i++;
		}
		posX = m_tiles[i].getX();
		posY = m_tiles[i].getY();
		letter = m_tiles[i].getTile().getLetter();
		if (cond)
			renderTileInMov(posX, posY, letter);
	}
}

/**
* Metodo que llama a la libreria grafica
* y imprime fichas en movimiento
*/
void Player::renderTileInMov(float posX, float posY, char letter)
{
	switch (letter)
	{
	case 'a': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_A_SMALL, posX, posY);
		break;
	case 'b': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_B_SMALL, posX, posY);
		break;
	case 'c': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_C_SMALL, posX, posY);
		break;
	case 'd': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_D_SMALL, posX, posY);
		break;
	case 'e': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_E_SMALL, posX, posY);
		break;
	case 'f': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_F_SMALL, posX, posY);
		break;
	case 'g': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_G_SMALL, posX, posY);
		break;
	case 'h': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_H_SMALL, posX, posY);
		break;
	case 'i': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_I_SMALL, posX, posY);
		break;
	case 'j': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_J_SMALL, posX, posY);
		break;
	case 'k': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_K_SMALL, posX, posY);
		break;
	case 'l': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_L_SMALL, posX, posY);
		break;
	case 'm': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_M_SMALL, posX, posY);
		break;
	case 'n': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_N_SMALL, posX, posY);
		break;
	case 'o': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_O_SMALL, posX, posY);
		break;
	case 'p': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_P_SMALL, posX, posY);
		break;
	case 'q': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Q_SMALL, posX, posY);
		break;
	case 'r': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_R_SMALL, posX, posY);
		break;
	case 's': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_S_SMALL, posX, posY);
		break;
	case 't': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_T_SMALL, posX, posY);
		break;
	case 'u': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_U_SMALL, posX, posY);
		break;
	case 'v': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_V_SMALL, posX, posY);
		break;
	case 'w': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_W_SMALL, posX, posY);
		break;
	case 'x': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_X_SMALL, posX, posY);
		break;
	case 'y': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Y_SMALL, posX, posY);
		break;
	case 'z': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Z_SMALL, posX, posY);
		break;
	}
}

/**
* Metodo que llama a la libreria grafica
* y imprime fichas en la mano
*/
void Player::renderTileStatic(float posX, float posY, char letter)
{
	switch (letter)
	{
	case 'a': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_A_BIG, posX, posY);
		break;
	case 'b': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_B_BIG, posX, posY);
		break;
	case 'c': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_C_BIG, posX, posY);
		break;
	case 'd': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_D_BIG, posX, posY);
		break;
	case 'e': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_E_BIG, posX, posY);
		break;
	case 'f': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_F_BIG, posX, posY);
		break;
	case 'g': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_G_BIG, posX, posY);
		break;
	case 'h': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_H_BIG, posX, posY);
		break;
	case 'i': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_I_BIG, posX, posY);
		break;
	case 'j': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_J_BIG, posX, posY);
		break;
	case 'k': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_K_BIG, posX, posY);
		break;
	case 'l': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_L_BIG, posX, posY);
		break;
	case 'm': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_M_BIG, posX, posY);
		break;
	case 'n': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_N_BIG, posX, posY);
		break;
	case 'o': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_O_BIG, posX, posY);
		break;
	case 'p': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_P_BIG, posX, posY);
		break;
	case 'q': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Q_BIG, posX, posY);
		break;
	case 'r': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_R_BIG, posX, posY);
		break;
	case 's': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_S_BIG, posX, posY);
		break;
	case 't': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_T_BIG, posX, posY);
		break;
	case 'u': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_U_BIG, posX, posY);
		break;
	case 'v': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_V_BIG, posX, posY);
		break;
	case 'w': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_W_BIG, posX, posY);
		break;
	case 'x': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_X_BIG, posX, posY);
		break;
	case 'y': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Y_BIG, posX, posY);
		break;
	case 'z': GraphicManager::getInstance()->drawSprite(IMAGE_LETTER_Z_BIG, posX, posY);
		break;
	}
}

/**
* Metodo que pone todas la fichas
* en su posicion inicial
*/
void Player::recall(int i)
{
	//m_inBoard[i] = false;
	m_tiles[i].setPos(m_posInicalsX[i], POS_Y);
	m_tiles[i].setEmpty(false);
	m_tiles[i].setOnBoard(false);
	m_algunaJugada = false;
	m_moviment = false;
	int j = 0;
	BoardPosition bp(-1, -1);
	m_tiles[i].setBoardPosition(bp);
	while (!m_algunaJugada && j < MAX_TILES)
	{
		if (m_tiles[j].getOnBoard())
			m_algunaJugada = true;
		j++;
	}
}


/**
* Metodo que pone todas la fichas
* en su posicion inicial y mezcla
* las fichas
*/
void Player::shuffle()
{
	srand(time(NULL));
	for (int i = 0; i < MAX_TILES; i++)
	recall(i);
	PlayerTile tilesAux[MAX_TILES];
	int aux = MAX_TILES;
	int ordreRandom[MAX_TILES] = { -1,-1,-1,-1,-1,-1,-1 };
	
	for (int i = 0; i < MAX_TILES; i++)
	{
		int j = 0;
		bool doble = false;
		int randomNumber = rand() % MAX_TILES;
		while (ordreRandom[j] != -1 && !doble && j < MAX_TILES)
		{
			if (randomNumber == ordreRandom[j])
				doble = true;
			else
				j++;
		}
		if (!doble)
		{
			ordreRandom[i] = randomNumber;
		}
		else
			i--;
		
	}
	for (int i = 0; i < MAX_TILES; i++)
	{
		m_tiles[i].setPos(m_posInicalsX[ordreRandom[i]], POS_Y);
		tilesAux[ordreRandom[i]] = m_tiles[i];
	}

	for (int i = 0; i < MAX_TILES; i++)
		m_tiles[i] = tilesAux[i];
}

/**
* Metodo que coge una ficha de
* la bolsa cuando una ficha pasa a
* formar parte del tablero
*/
void Player::rellenar(Tile t, int i)
{
	
	if (m_tiles[i].getOnBoard())
	{
		m_tiles[i].setTile(t);
	}
	recall(i);
}



//BoardPosition bp = m_players[m_currentPlayer].getPlayerTile(i).getBoardPosition();
//m_board.setTile(t, bp);
//setInBoard(i, true);


		/*else if (m_tiles[i].getEmpty() && m_moviment && !m_tiles[i].getOnBoard())
		{
			m_tiles[i].setPos(m_posInicalsX[i], POS_Y);
			m_tiles[i].setEmpty(false);
			m_tiles[i].setOnBoard(false);
			m_algunaJugada = false;
			m_moviment = false;
		}*/
		/*else if (!mouseIsPressed &&
		mousePosX > BOARD_POS_X &&
		mousePosY > BOARD_POS_Y &&
		mousePosX < BOARD_POS_X + BOARD_SIZE &&
		mousePosY < BOARD_POS_Y + BOARD_SIZE &&*/