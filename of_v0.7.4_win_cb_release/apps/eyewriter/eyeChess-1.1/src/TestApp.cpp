#include "TestApp.h"
#include "stdio.h"


//--------------------------------------------------------------
TestApp::TestApp()
{

}

//--------------------------------------------------------------
void TestApp::setup()
{
    //ofToggleFullscreen();
    //---- setup standard application settings

    ofxXmlSettings XML;
    XML.loadFile("settings/globalSettings.xml"); //in app/bin/data/settings
    buttonSensitivity = XML.getValue("app:button:sensitivity", 0.0);

    ofSetVerticalSync(true);

    mode = MODE_CHESS;

    TM.setup();
    CM.setup();
    testScene.setup();
    eyeApp.setup();
    chessScene.setup();

    eyeSmoothed.set(0,0,0);

    bMouseSimulation = false;
    bMouseEyeInputSimulation = false;

}

//--------------------------------------------------------------
void TestApp::update()
{

    ofBackground(70,70,70);

    // update the tracking manager (and internally, its input manager)
    TM.update();

    // update the calibration manager
    CM.update();


    if (CM.bAutomatic == true && CM.bAmInAutodrive == true && CM.bInAutoRecording)
    {

        if (TM.bGotAnEyeThisFrame())
        {
            ofPoint trackedEye = TM.getEyePoint();
            CM.fitter.registerCalibrationInput(trackedEye.x,trackedEye.y);
            CM.inputEnergy = 1;
        }
    }

    // smooth eye data in...
    if (!bMouseSimulation)
    {
        if (CM.fitter.bBeenFit)
        {
            ofPoint trackedEye;

            if (bMouseEyeInputSimulation)
            {
                trackedEye.x = mouseX;
                trackedEye.y = mouseY;
            }
            else
            {
                trackedEye = TM.getEyePoint();
            }

            //cout << CM.smoothing << endl;
            CM.smoothing = 0.7;
            ofPoint screenPoint = CM.fitter.getCalibratedPoint(trackedEye.x, trackedEye.y);
            eyeSmoothed.x = CM.smoothing * eyeSmoothed.x + (1-CM.smoothing) * screenPoint.x;
            eyeSmoothed.y = CM.smoothing * eyeSmoothed.y + (1-CM.smoothing) * screenPoint.y;
        }
    }
    else
    {
        eyeSmoothed.x = mouseX;
        eyeSmoothed.y = mouseY;
    }

    if( mode == MODE_DRAW )
    {
        ofPoint pt = eyeSmoothed;
        eyeApp.update( pt.x, pt.y);
    }


    if (mode == MODE_TEST)
    {
        ofPoint pt = eyeSmoothed;
        testScene.update(pt.x, pt.y);
    }

    if( mode == MODE_CHESS)
    {
         ofPoint pt = eyeSmoothed;
        chessScene.update( pt.x, pt.y);
    }
}


//--------------------------------------------------------------
void TestApp::draw()
{


    ofSetColor(255, 255, 255);


    if (mode == MODE_TRACKING)			TM.draw();
    if (mode == MODE_CALIBRATING)		CM.draw();
    if (mode == MODE_TEST)				testScene.draw();
    if (mode == MODE_DRAW )				eyeApp.draw();
    if (mode == MODE_CHESS )			chessScene.draw();


    // draw a green dot to see how good the tracking is:
    if (CM.fitter.bBeenFit || bMouseSimulation)
    {
        if( mode != MODE_DRAW && mode != MODE_CHESS)
        {
            ofSetColor(0,255,0,120);
            ofFill();
            ofCircle(eyeSmoothed.x, eyeSmoothed.y, 20);
        }
    }
}



//--------------------------------------------------------------
void TestApp::keyPressed(int key)
{


    switch (key)
    {

    case	OF_KEY_RETURN:
        mode ++;
        mode %= 5; // number of modes;
        break;
    case	'f':
    case	'F':
        ofToggleFullscreen();
        break;

    case	'm':
    case	'M':
        bMouseSimulation = !bMouseSimulation;
        break;
    }

    if (mode == MODE_CALIBRATING)		CM.keyPressed(key);
}

//--------------------------------------------------------------
void TestApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void TestApp::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void TestApp::mouseDragged(int x, int y, int button)
{

    if (mode == MODE_TRACKING)			TM.mouseDragged(x, y, button);
    if (mode == MODE_CALIBRATING)		CM.mouseDragged(x, y, button);
    if (mode == MODE_TEST)              testScene.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void TestApp::mousePressed(int x, int y, int button)
{


    if (mode == MODE_TRACKING)			TM.mousePressed(x, y, button);
    if (mode == MODE_CALIBRATING)		CM.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void TestApp::mouseReleased(int x, int y, int button)
{

    if (mode == MODE_TRACKING)			TM.mouseReleased();
    if (mode == MODE_CALIBRATING)		CM.mouseReleased(x,y,button);
}


//--------------------------------------------------------------
void TestApp::resized(int w, int h)
{

}


