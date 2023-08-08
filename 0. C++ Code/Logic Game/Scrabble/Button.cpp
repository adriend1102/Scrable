//
//  Button.cpp

#include "Button.h"

/**
* Constructor con parametros
 */
Button::Button(IMAGE_NAME state_normal,
               IMAGE_NAME state_pressed,
               int posX, int posY,
               int width, int height)
{
    m_eCurrentState = NORMAL;
    m_iPosX = posX;
    m_iPosY = posY;
    m_iWidth = width;
    m_iHeight = height;
    m_eStateNormal = state_normal;
    m_eStatePressed = state_pressed;
}

/**
* Destructor por defecto
 */
Button::~Button(){
}

/**
* Constructor por defecto
 */
Button::Button()
{
    m_eCurrentState = NORMAL;
    m_iPosX = 0;
    m_iPosY = 0;
    m_iWidth = 0;
    m_iHeight = 0;
}

/**
* metodo que actualiza el
* estado del boton
 */
bool Button::update ( int mousePosX, int mousePosY, bool mouseIsPressed) {

    bool l_bDoAction = false;
    if (mousePosX >= m_iPosX && mousePosX <= m_iPosX + m_iWidth &&
        mousePosY >= m_iPosY && mousePosY <= m_iPosY + m_iHeight)
    {
        if (mouseIsPressed && m_eCurrentState == NORMAL) {
            m_eCurrentState = PRESSED; //Hem entrat amb el mouse apretant --> no fer res.
        }
        else if (!mouseIsPressed && m_eCurrentState == PRESSED)
        {
            l_bDoAction = true;
            m_eCurrentState = NORMAL;
        }
    }
    else
        m_eCurrentState = NORMAL;
    return l_bDoAction;
}

/**
* Metodo que imprime el boton
* segun el estado
 */
void Button::render () {
    //TODO 4.2: Implementar la programació del render...
    if (m_eCurrentState == ButtonState::PRESSED)
        GraphicManager::getInstance()->drawSprite(m_eStatePressed, m_iPosX, m_iPosY);
    else
        GraphicManager::getInstance()->drawSprite(m_eStateNormal, m_iPosX, m_iPosY);
}

