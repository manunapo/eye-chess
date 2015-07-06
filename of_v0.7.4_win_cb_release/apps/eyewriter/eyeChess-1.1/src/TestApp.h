#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "TestApp.h"
#include "TrackingManager.h"
#include "CalibrationManager.h"
#include "TestingScene.h"
#include "EyePlotterTestApp.h"
#include "ChessTestApp.h"


enum
{

    MODE_TRACKING,  MODE_CALIBRATING, MODE_CHESS

};


class TestApp : public ofBaseApp
{

public:

    TestApp();
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void resized(int w, int h);

    bool bMouseSimulation;
    bool bMouseEyeInputSimulation;

    ofPoint eyeSmoothed;

    int mode;

    //----- scenes

    TrackingManager			TM;
    CalibrationManager		CM;
    TestingScene            testScene;
    EyePlotterTestApp       eyeApp;
    ChessTestApp            chessScene;

    //------ drawing
    void drawHelp();

    float buttonSensitivity;
};

#endif
