#pragma once

#include "ofMain.h"
#include "buttonStateManager.h"
#include "buttonState.h"

#include "ButtonRect.h"
#include "ButtonToggle.h"
#include "ButtonTrigger.h"

#include "BaseScene.h"
#include "ChessBoard.h"

class ChessScene : public BaseScene
{
protected:
    ButtonState	testState;
    ButtonStateManager button;

    ButtonTrigger boxButtons[8][8];

    ChessBoard * board;

    float lastX;
    float lastY;

    float w;
    float h;
    float chessBoxSize;
    float iniX;
    float iniY;
    float rectH;
    float rectW;

    void initButtons();
    bool sizeChanged();
    void relocateButtons();
    void updateParameters();

public:
    void setup();
    void update(float mouseX, float mouseY);
    void draw();

};