//
//  Button.hpp
#pragma once

#include <stdio.h>
#include <string>
#include "../GraphicManager.h"

using namespace std;

typedef enum {
    NORMAL = 0,
    PRESSED,
    NONE
} ButtonState;

/**
* CLASS Button
* Classe que permite guardar informacion de un
* boton, actualizar su estado, y imprimirlo
* para esto tiene atributos como:
* la posicion del boton, el estado, las
* dimensiones, y las imagenes que se usan
 */
class Button
{
public:


    Button(IMAGE_NAME state_normal,
           IMAGE_NAME state_pressed,
           int posX, int posY,
           int width, int height);

    ~Button();

    Button();

    bool update ( int mousePosX, int mousePosY, bool mouseIsPressed);
    void render ();

private:
    ButtonState m_eCurrentState;
    int         m_iPosX;
    int         m_iPosY;
    int         m_iWidth;
    int         m_iHeight;
    IMAGE_NAME  m_eStateNormal;
    IMAGE_NAME  m_eStatePressed;
};

