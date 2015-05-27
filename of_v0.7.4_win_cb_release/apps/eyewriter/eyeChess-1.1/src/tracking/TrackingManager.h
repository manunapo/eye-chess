#ifndef _TRACKSCENE_H
#define _TRACKSCENE_H


#include "ofMain.h"
#include "EyeTracker.h"
#include "ofxControlPanel.h"
#include "InputManager.h"

class TrackingManager
{

public:
    TrackingManager();
    ~TrackingManager();

    void setup();
    void update();
    void draw();

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();

    void setupGui();
    void updateGui();

    void trackEyes();

    // open video settings panel if using a camera
    void videoSettings();

    // returns the tracked pupil centroid
    ofPoint	getEyePoint();
    bool	bGotAnEyeThisFrame();


    ofxControlPanel		panel;

    //----- video sources... what are we tracking!

    InputManager		IM;

    EyeTracker			tracker;

    int					minBlob, maxBlob;
    float				threshold;
    bool				bFoundEye;
    ofPoint				eyePoint;

    //---- button settings
    float               buttonPressTime;
    float       getButtonPressTime();


};

#endif
