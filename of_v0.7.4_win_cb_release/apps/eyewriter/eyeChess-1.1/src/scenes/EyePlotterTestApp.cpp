#include "EyePlotterTestApp.h"
#include "TestApp.h"

int buttonCount = 1.0f;
float rate = 1.8;
float ptThreshold = 7.0f;

float timer = -5.0;
float smoothPct = 0.4;

//--------------------------------------------------------------
void EyePlotterTestApp::setup()
{

    scene = &drawing;

    scene->setup();

    mx = 0;
    my = 0;
}

//--------------------------------------------------------------
void EyePlotterTestApp::update(float mouseX, float mouseY)
{

    float mousex = mouseX;
    float mousey = mouseY;

    mx *= (1.0-smoothPct);
    mx += smoothPct * (float)mousex;

    my *= (1.0-smoothPct);
    my += smoothPct * (float)mousey;

    scene->update(mx, my);

}


//--------------------------------------------------------------
void EyePlotterTestApp::draw()
{
    ofPushStyle();

    ofFill();
    ofSetColor(10, 20, 10);
    ofRect(ofGetWidth() - SIDE_GUI_X, 0, SIDE_GUI_X, ofGetHeight());

    ofSetColor(220, 220, 220);
    ofRect(0, 0, ofGetWidth() - SIDE_GUI_X, ofGetHeight());

    scene->draw();

    if( ofGetElapsedTimef() - timer < 3.0 )
    {
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("ptThresh is "+ofToString(ptThreshold, 1) + "\nrate is "+ofToString(rate, 1)
                           + "\nbuttonCount is "+ofToString(buttonCount)
                           + "\nsmoothPct is "+ofToString(smoothPct), 200, 200);
    }

    ofPopStyle();
}

//--------------------------------------------------------------
void EyePlotterTestApp::keyPressed  (int key)
{

    //GHETTO SETTINGS QUICKLY HACKED

    if(key == '=') ptThreshold += 0.8;
    if(key == '-') ptThreshold -= 0.8;

    if(key == ']') rate += 0.1;
    if(key == '[') rate -= 0.1;

    if(key == '.') buttonCount ++;
    if(key == ',') buttonCount --;

    if(key == 'm') smoothPct -= 0.05;
    if(key == 'n') smoothPct += 0.05;

    ptThreshold = ofClamp(ptThreshold, 2.0, 20.0);
    rate = ofClamp(rate, 0.1, 5.0);
    buttonCount = ofClamp(buttonCount, 10, 120);

    smoothPct = ofClamp(smoothPct, 0, 1);

    buttonCount = ((TestApp *)ofGetAppPtr())->buttonSensitivity;

    ghettoSettings.setValue("buttonCount", buttonCount);
    ghettoSettings.setValue("rate", rate);
    ghettoSettings.setValue("ptThreshold", ptThreshold);
    ghettoSettings.setValue("smoothPct", smoothPct);

    ghettoSettings.saveFile("settings.xml");

    if( key == 'e')
    {
    }

    //show settings on screen for a few seconds
    timer = ofGetElapsedTimef();

}

//--------------------------------------------------------------
void EyePlotterTestApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void EyePlotterTestApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void EyePlotterTestApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void EyePlotterTestApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void EyePlotterTestApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void EyePlotterTestApp::resized(int w, int h)
{

}

