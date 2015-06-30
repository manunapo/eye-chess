#pragma once
#include "ButtonTrigger.h"

class ButtonMatrix
{
private:
    ButtonTrigger* buttons[8][8];

public:
    ButtonMatrix();
    void put(ButtonTrigger* btn, int f, int r);
    ButtonTrigger* get(int f, int r);
};
