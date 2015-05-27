#include "ChessScene.h"

//switch to gui
extern int buttonCount;
extern float rate;
extern float ptThreshold;

//--------------------------------------------------------------
void ChessScene::setup()
{
    board = new ChessBoard();

    lastX = 0;
    lastY = 0;

    mx = 0.0;
    my = 0.0;

    iniX = 0;
    iniY = 0;
    w = 0;
    h = 0;

    button.setWaitTime( rate );

    testState = BUTTON_NONE;

    updateParameters();

    initButtons();
}

//--------------------------------------------------------------
void ChessScene::update(float mouseX, float mouseY)
{
    button.setWaitTime( rate );

    if(sqrt(pow(lastX - mouseX, 2) + pow(lastY - mouseY, 2)) > 25)
    {
        mx = mouseX;
        my = mouseY;
        lastX = mx;
        lastY = my;
    }
    else
    {
        mx = lastX;
        my = lastY;
    }
    bool checkDraw = true;
    if(testState == BUTTON_NONE && mx > (ofGetWidth() - SIDE_GUI_X))
    {
        checkDraw = false;
        button.clear();
    }

    if( checkDraw )
    {
        button.update(mx, my);
        bool stopped = button.isPointStationary(ptThreshold);

        if( stopped )
        {
            if( testState == BUTTON_NONE )
            {
                testState = BUTTON_STARTED;
            }
            else if( testState == BUTTON_STARTED )
            {
                testState = BUTTON_NONE;
            }
        }
    }

    //check for adding our point
    if( testState == BUTTON_STARTED )
    {

        testState = BUTTON_NONE;
    }

    relocateButtons();
    updateParameters();


    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(boxButtons[i][j].update(mx, my))
            {
                printf("hola %i - %i",i,j);
            }
        }
    }

}

//--------------------------------------------------------------
void ChessScene::draw()
{
    ofPushStyle();
    ofBackground(220,220,220);

    ofPushStyle();
    ofFill();
    ofRect(0,0, rectW, rectH);
    if(iniY == 0)
        ofRect(iniX + w,iniY,rectW,rectH);
    else
        ofRect(iniX, iniY + h,rectW,rectH);
    ofPopStyle();

    ofPushStyle();
    ofSetLineWidth(1.0);
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0);

    ///drawing the grid
    for(int x = 0; x < 9; x++)
    {
        ofLine(iniX + x*chessBoxSize, iniY, iniX + x*chessBoxSize, iniY + w);
    }

    for(int y = 0; y < 9; y++)
    {
        ofLine(iniX, iniY + y*chessBoxSize, iniX + w, iniY + y*chessBoxSize);
    }

    ofPopStyle();
    ///end drawing the grid-----


    for(int i = 0; i < drawableButtons.size(); i++)
    {
        drawableButtons[i]->draw();
    }

    if( true )
    {
        ofPushStyle();
        ofFill();
        ofSetColor(255, 255, 255);
        ofCircle(mx, my, 9);
        ofSetColor(0,0,0);
        ofCircle(mx, my, 6);
        ofPopStyle();
    }
    else if( testState == BUTTON_NONE )
    {
        ofSetColor(0, 0, 0, 80);
        ofNoFill();
        ofCircle(mx, my, 9);
    }
    else if(testState == BUTTON_STARTED )
    {
        ofFill();
        ofCircle(mx, my, 5);
    }

    ofPopStyle();

}

void ChessScene::updateParameters()
{
    w = ofGetWidth();
    h = ofGetHeight();

    if(w < h)
    {
        iniY = (h - w) / 2;
        iniX = 0;
        rectH = iniY;
        rectW = w;
        h = w;
    }
    else
    {
        iniX = (w - h) / 2;
        iniY = 0;
        rectH = h;
        rectW = iniX;
        w = h;
    }
    chessBoxSize = w/8;
}

void ChessScene::relocateButtons()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(board->isFree(i,j))
                boxButtons[i][j].setup("", iniX + j*chessBoxSize, iniY + i*chessBoxSize, chessBoxSize, chessBoxSize);
            else
                boxButtons[i][j].setup("", board->getImage(i,j), iniX + j*chessBoxSize, iniY + i*chessBoxSize, chessBoxSize, chessBoxSize);
        }
    }
}

void ChessScene::initButtons()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            boxButtons[i][j].setup("S", iniX + j*chessBoxSize, iniY + i*chessBoxSize, chessBoxSize, chessBoxSize);
            drawableButtons.push_back(&boxButtons[i][j]);
            boxButtons[i][j].setMaxCounter(buttonCount);
        }
    }
}
