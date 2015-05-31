#include "ChessTestApp.h"


//--------------------------------------------------------------
void ChessTestApp::setup()
{
    scene = &chess;

    scene->setup();

    mx = 0;
    my = 0;



}

//--------------------------------------------------------------
void ChessTestApp::update(float mouseX, float mouseY)
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
void ChessTestApp::draw()
{
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
void ChessTestApp::keyPressed  (int key)
{


}

//--------------------------------------------------------------
void ChessTestApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ChessTestApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ChessTestApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ChessTestApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ChessTestApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ChessTestApp::resized(int w, int h)
{

}
