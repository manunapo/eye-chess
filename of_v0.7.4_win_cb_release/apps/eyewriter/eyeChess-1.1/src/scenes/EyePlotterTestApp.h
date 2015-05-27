#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "BaseScene.h"
#include "DrawingScene.h"

#include "ButtonTrigger.h"

#include "Defines.h"

class EyePlotterTestApp
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

    float mx, my;

    BaseScene * scene;

    DrawingScene drawing;

    ofxXmlSettings ghettoSettings;
};

