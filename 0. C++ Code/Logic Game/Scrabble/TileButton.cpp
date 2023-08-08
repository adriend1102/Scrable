#include "TileButton.h"

int TileButton::update(int mousePosX, int mousePosY, bool mouseIsPressed)
{
    //1 esperando a ser cogida 2 en desplazamiento 3 en el tablero
    int status = 0;
    if (mousePosX >= m_iPosX && mousePosX <= m_iPosX + btn_size_h &&
        mousePosY >= m_iPosY && mousePosY <= m_iPosY + btn_size_h &&
        m_tileStatus == NORMAL ||
        mousePosX >= m_iPosX && mousePosX <= m_iPosX + BOARD_TILE_SIZE &&
        mousePosY >= m_iPosY && mousePosY <= m_iPosY + BOARD_TILE_SIZE &&
        m_tileStatus == NORMAL)
    {
        if (mouseIsPressed && m_tileStatus != IN_MOVEMENT) {
            m_tileStatus = IN_MOVEMENT; //Hem entrat amb el mouse apretant --> no fer res.
        }
        else if (!mouseIsPressed && m_eCurrentState == PRESSED)
        {
            l_bDoAction = true;
            m_eCurrentState = NORMAL;
        }
    }
    else
        m_eCurrentState = NORMAL;
	return 0;
}

void TileButton::render()
{
}
