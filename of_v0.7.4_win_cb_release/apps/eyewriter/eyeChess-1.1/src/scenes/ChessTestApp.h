#pragma once
#include "BaseScene.h"
#include "chess/ChessScene.h"

class ChessTestApp
{

public:

    void setup();
    void update(float mouseX, float mouseY);
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void resized(int w, int h);

private:
    float mx, my;

    BaseScene * scene;

    ChessScene chess;

    int buttonCount = 1.0f;
    float rate = 1.8;
    float ptThreshold = 7.0f;

    float timer = -5.0;
    float smoothPct = 0.4;
};

