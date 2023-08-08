//
//  Cell.cpp
//  Scrabble
//


#include "Cell.h"

/**
* Metodo que permite imprimir las casillas
 */
void Cell::render(float posX, float posY)
{
	if (!m_empty)
	{
		char letter = m_tile.getLetter();

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
}
