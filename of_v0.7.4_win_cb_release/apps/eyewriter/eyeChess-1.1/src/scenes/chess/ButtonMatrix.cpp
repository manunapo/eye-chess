#include "ButtonMatrix.h"

ButtonMatrix::ButtonMatrix()
{
    for(int i = 0; i < 8; i++)
    {
        for( int j = 0; j < 8; j++)
        {
            buttons[i][j] = new ButtonTrigger();
        }
    }
}

void ButtonMatrix::put(ButtonTrigger* btn, int f, int r)
{
    buttons[f][r] = btn;
}

ButtonTrigger* ButtonMatrix::get(int f, int r)
{
    return buttons[f][r];
}
