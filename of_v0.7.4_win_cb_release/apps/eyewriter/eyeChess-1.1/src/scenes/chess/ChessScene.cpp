#include "ChessScene.h"
#include "ButtonMatrix.cpp"

//switch to gui
extern int buttonCount;
extern float rate;
extern float ptThreshold;

//--------------------------------------------------------------
void ChessScene::setup()
{
    board = new ChessBoard();
    boxButtons = new ButtonMatrix();

    lastX = 0;
    lastY = 0;

    mx = 0.0;
    my = 0.0;

    iniX = 0;
    iniY = 0;
    w = 0;
    h = 0;

    button.setWaitTime( rate );

    updateParameters();

    endGameButton.setup("END", 0, 0, 50, 50);
    drawableButtons.push_back(&endGameButton);
    endGameButton.setMaxCounter(buttonCount);

    testState = BUTTON_NONE;

    initButtons();

    playerOne.loadFont("fonts/arial.ttf", 20);
    playerTwo.loadFont("fonts/arial.ttf", 20);
}

void ChessScene::endGame()
{
    board->endGame();
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

    if( endGameButton.update( mx, my) )
    {
        endGame();
    }

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(boxButtons->get(i, j)->update(mx, my))
            {
                cout << "selected: " << i << "-" << j;
                if(board->hasTurn())
                {
                    board->boxSelected( boxButtons, i, j);
                }
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
    ofSetColor(168,130,79);
    ofRect(0,0, rectW, rectH);


    if(iniY == 0)
    {
        ofSetColor(224,180,121);
        ofSetColor(168,130,79);
        ofRect(iniX + w,iniY,rectW,rectH);
    }
    else
    {
        ofRect(iniX, iniY + h,rectW,rectH);
    }

    ofPopStyle();

    ofPushStyle();
    ofSetLineWidth(1.0);
    ofEnableAlphaBlending();

    bool black = false;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(black)
            {
                //ofSetColor(89,97,97);
                ofSetColor(0,0,0);
            }
            else
            {
                //ofSetColor(242, 230, 213);
                ofSetColor(255,255,255);
            }
            ofRect( iniX + x*chessBoxSize, iniY + y*chessBoxSize, chessBoxSize, chessBoxSize);
            black = !black;
        }
        black = !black;
    }

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

    buildOptionsBar();

}

void ChessScene::updateParameters()
{
    w = ofGetWidth() - OPTIONS_BAR_WIDTH;
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
                boxButtons->get(i, j)->setup("", iniX + j*chessBoxSize, iniY + i*chessBoxSize, chessBoxSize, chessBoxSize);
            else
                boxButtons->get(i, j)->setup("", board->getImage(i,j), iniX + j*chessBoxSize, iniY + i*chessBoxSize, chessBoxSize, chessBoxSize);
        }
    }
}

void ChessScene::initButtons()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            boxButtons->get(i, j)->setup("S", iniX + j*chessBoxSize, iniY + i*chessBoxSize, chessBoxSize, chessBoxSize);
            drawableButtons.push_back(boxButtons->get(i, j));
            boxButtons->get(i, j)->setMaxCounter(buttonCount);
        }
    }
}

void ChessScene::buildOptionsBar()
{
    float auxX = ofGetWidth() - OPTIONS_BAR_WIDTH;

    ofSetColor(0,0,0);
    ofRect(auxX, 0, OPTIONS_BAR_WIDTH, ofGetHeight());
    ofSetColor(128,97,56);
    ofRect(auxX+OPTIONS_BAR_BORDER, OPTIONS_BAR_BORDER, OPTIONS_BAR_WIDTH - OPTIONS_BAR_BORDER*2, ofGetHeight()-OPTIONS_BAR_BORDER*2);

    ofSetColor(0,0,0);
    playerOne.drawString("PLAYER 1", auxX + 10, ofGetHeight() / 8);
    if(board->hasTurn())
        ofFill();
    else
        ofNoFill();
    ofCircle( auxX + OPTIONS_BAR_WIDTH / 2, ofGetHeight() / 8 + 35 , 20);



    playerTwo.drawString("PLAYER 2", auxX + 10, ofGetHeight() / 8 * 7);
    if(!board->hasTurn())
        ofFill();
    else
        ofNoFill();
    ofCircle( auxX + OPTIONS_BAR_WIDTH / 2, ofGetHeight() / 8 * 7 + 35 , 20);
}
