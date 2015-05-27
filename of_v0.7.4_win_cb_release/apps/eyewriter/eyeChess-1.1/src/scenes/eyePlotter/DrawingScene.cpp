/*
 *  drawingScene.cpp
 *  openFrameworks
 *
 *  Created by theo on 20/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "DrawingScene.h"

//switch to gui
extern int buttonCount;
extern float rate;
extern float ptThreshold;

//--------------------------------------------------------------
void DrawingScene::setup()
{
    lastX = 0;
    lastY = 0;

    isClosurePoint = true;

    ofBackground(255, 255, 255);

    //toggle drawing
    bDrawing = false;

    pause.setup("DRAWING", "WAITING", bDrawing, ofGetWidth() - SIDE_GUI_X + 10, 10, BUTTON_WIDTH, BUTTON_HEIGHT);
    nextStroke.setup("NEW STROKE", ofGetWidth() - SIDE_GUI_X + 10, BUTTON_HEIGHT + 100, BUTTON_WIDTH, BUTTON_HEIGHT);
    closeOutline.setup("CLOSE OUTLINE", ofGetWidth() - SIDE_GUI_X + 10, (BUTTON_HEIGHT * 2) + 110, BUTTON_WIDTH, BUTTON_HEIGHT);
    fillOutline.setup("FILL OUTLINE", ofGetWidth() - SIDE_GUI_X + 10, (BUTTON_HEIGHT * 3) + 120, BUTTON_WIDTH, BUTTON_HEIGHT);

    drawableButtons.push_back(&nextStroke);
    drawableButtons.push_back(&closeOutline);
    drawableButtons.push_back(&fillOutline);

    saveSettings.loadFile("counter.xml");

    preFix = saveSettings.getValue("session", "tempt-day1");
    count  = saveSettings.getValue("count", 0);

    mx = 0.0;
    my = 0.0;

    nextStroke.setMaxCounter(buttonCount);
    fillOutline.setMaxCounter(buttonCount);
    closeOutline.setMaxCounter(buttonCount);
    pause.setMaxCounter(buttonCount);

    button.setWaitTime( rate );

    if(strokeGroup.size() == 0 )
    {
        strokeGroup = StrokeGroup();
    }

    testState = BUTTON_NONE;
}

void DrawingScene::relocateButtons()
{
    pause.relocate( ofGetWidth() - SIDE_GUI_X + 10, 10);
    nextStroke.relocate( ofGetWidth() - SIDE_GUI_X + 10, BUTTON_HEIGHT + 100);
    closeOutline.relocate( ofGetWidth() - SIDE_GUI_X + 10, (BUTTON_HEIGHT * 2) + 110);
    fillOutline.relocate( ofGetWidth() - SIDE_GUI_X + 10, (BUTTON_HEIGHT * 3) + 120);
}

void DrawingScene::makeNewStroke()
{
    if( strokeGroup.size() )
    {
        //if we have a stroke already and the last stroke has 0 or just 1 point then just clear the points
        //and don't make a new stroke - ie recycle :)
        if( strokeGroup.size() && strokeGroup.getLastStrokeNumPoints() <= 1 )
        {
            strokeGroup.clearLast();
        }
        else
        {
            //otherwise make a new stroke.
            strokeGroup.begin();
        }
    }
    isClosurePoint = true;
}

void DrawingScene::makeFillOutline()
{

}

void DrawingScene::makeCloseOutline()
{
    if( strokeGroup.getLastStrokeNumPoints() >= 3 )
    {
        strokeGroup.addPoint(closurePoint.x, closurePoint.y);
        testState = BUTTON_NONE;
    }
}

//--------------------------------------------------------------
void DrawingScene::update(float mouseX, float mouseY)
{
    relocateButtons();

    nextStroke.setMaxCounter(buttonCount);
    fillOutline.setMaxCounter(buttonCount);
    closeOutline.setMaxCounter(buttonCount);
    pause.setMaxCounter(buttonCount);

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

    //UPDATE THE TOGGLE with mouse and get check toggle state
    if( pause.update(mx, my) )
    {
        bDrawing = pause.getState();
    }

    if( bDrawing )
    {

        if( nextStroke.update( mx, my) )
        {
            makeNewStroke();
        }
        if( closeOutline.update( mx, my))
        {
            makeCloseOutline();
        }
        if( fillOutline.update( mx, my))
        {
            makeFillOutline();
        }
    }

    bool checkDraw = true;
    if( !bDrawing || (testState == BUTTON_NONE && mx > (ofGetWidth() - SIDE_GUI_X)))
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
                strokeGroup.nextStroke();
            }
        }
    }

    //check for adding our point
    if( testState == BUTTON_STARTED )
    {
        //if we have more than 2 points check to see if the current point is close enough to the first point to close it completely
        if( strokeGroup.getLastStrokeNumPoints() >= 3 )
        {
            ofPoint point = strokeGroup.getFirstVertexOfLastStroke();
            ofPoint mouse( mx, my);
            if( point.distance( mouse) <= 12 )
            {
                mx = point.x;
                my = point.y;
            }
        }
        //add our point
        strokeGroup.addPoint( mx, my);
        if(isClosurePoint)
        {
            closurePoint = ofPoint( mx, my);
            isClosurePoint = false;
        }
        testState = BUTTON_NONE;
    }
}

//--------------------------------------------------------------
void DrawingScene::draw()
{
    ofPushStyle();

    ///drawing the grid-----
    float w = ofGetWidth();
    float h = ofGetHeight();

    ofPushStyle();

    ofSetLineWidth(1.0);
    ofEnableAlphaBlending();
    ofSetColor(0, 0, 0, 20);

    for(int x = 0; x < (w - SIDE_GUI_X); x += 20)
    {
        ofLine(x, 0, x, h);
    }

    for(int y = 0; y < h; y+= 20)
    {
        ofLine(0, y, w - SIDE_GUI_X, y);
    }

    ofPopStyle();
    ///end drawing the grid-----

    if(bDrawing)
    {
        for(int i = 0; i < drawableButtons.size(); i++)
        {
            drawableButtons[i]->draw();
        }

        ///draw the stipple temporal line
        if( strokeGroup.size() && strokeGroup.hasPoints() && mx > SIDE_GUI_X )
        {
            if( !strokeGroup.isNewStrokeOnNext() )
            {
                ofSetColor(0, 0, 0, 80);
                ofPoint pt = strokeGroup.getLastPoint();
                glLineStipple(1, 0x3F07 );
                glEnable( GL_LINE_STIPPLE );
                ofLine(mx, my, pt.x, pt.y);
                glDisable(GL_LINE_STIPPLE);
            }
        }
        ///end drawin stipple line
    }

    pause.draw();

    if( strokeGroup.size() )
    {
        ofEnableAlphaBlending();
        ofSetColor(0, 0, 0, 30);
        ofSetHexColor(0x000000);
        strokeGroup.draw();
    }

    if( mx > ofGetWidth() - SIDE_GUI_X )
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
