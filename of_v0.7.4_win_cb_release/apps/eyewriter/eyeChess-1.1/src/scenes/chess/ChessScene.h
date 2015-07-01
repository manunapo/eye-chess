#pragma once

#define OPTIONS_BAR_WIDTH 150
#define OPTIONS_BAR_BORDER 2

#include "ofMain.h"
#include <iostream>
#include "buttonStateManager.h"
#include "buttonState.h"

#include "ButtonRect.h"
#include "ButtonToggle.h"
#include "ButtonTrigger.h"

#include "BaseScene.h"
#include "ButtonMatrix.h"
#include "pieces/ChessBoard.h"


class ChessScene : public BaseScene
{
protected:
    ButtonState	testState;
    ButtonStateManager button;

    ButtonMatrix* boxButtons;
    ButtonTrigger endGameButton;

    ChessBoard* board;

    ofTrueTypeFont playerOne;
    ofTrueTypeFont playerTwo;

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
    void endGame();
    void buildOptionsBar();

public:
    void setup();
    void update(float mouseX, float mouseY);
    void draw();

};
