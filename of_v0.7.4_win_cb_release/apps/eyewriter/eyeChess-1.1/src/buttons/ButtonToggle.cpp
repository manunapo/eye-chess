/*
 *  buttonToggle.cpp
 *  openFrameworks
 *
 *  Created by theo on 17/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ButtonToggle.h"
#include "TestApp.h"

ButtonToggle::ButtonToggle()
{

    active  = false;
    hasLeft = true;
    counter = 0.0f;
    //maxCount = ((testApp *)ofGetAppPtr())->buttonSensitivity;
    //maxCount = 1.0f;
}

void ButtonToggle::setMaxCounter(float nCounter)
{
    maxCount = nCounter;
}

void ButtonToggle::setup( string onName, string offName,  bool startsActive, float xIn, float yIn, float w, float h)
{

    maxCount = ((TestApp *)ofGetAppPtr())->buttonSensitivity;

    displayText[1] = onName;
    displayText[0] = offName;

    active = startsActive;

    x		= xIn;
    y		= yIn;
    width	= w;
    height	= h;
}

void ButtonToggle::relocate(float newX, float newY)
{
    x = newX;
    y = newY;
}

bool ButtonToggle::update(float xIn, float yIn)
{


    bool changed = false;

    float currentTime = ofGetElapsedTimef();

    if( inRect(xIn, yIn) )
    {
        if(!turned)
        {
            if (firstTrigger)
            {
                timeStamp = currentTime;
                //cout << "hover timestamp: " << timeStamp << endl;
                turned = true;
                firstTrigger = false;
            }
        }

        else
        {
            float timeDiff = currentTime - timeStamp;
            //cout << "timeDiff " << timeDiff << endl;
            pct = timeDiff/maxCount;

            if (timeDiff >= maxCount)
            {
                active = !active;
                changed = true;
                //cout << "BUTTON TRIGGERED" << endl;
                turned = false;
                timeStamp = currentTime;
                pct = 0.0f;
            }
        }
    }
    else   //mouse not inRect
    {
        turned = false;
        firstTrigger = true;
        pct = 0.0f;
    }

    return changed;
}

bool ButtonToggle::getState()
{
    return active;
}

void ButtonToggle::draw(float opacity)
{
    ofFill();

    float pctActive = ofMap(pct, 0.0, 1.5, 0.0, 110.0);
    if( !active )
    {
        ofSetColor(160 - pctActive, 160 + pctActive, 160 - pctActive, opacity);
        //ofSetColor(180 - pctActive, 180.0, 180 - pctActive);
    }
    else
    {
        ofSetColor(10 + pctActive, 240 - pctActive, 10 + pctActive, opacity);
        //ofSetColor(100 + pctActive, 180, 100 + pctActive);
    }
    ofRect(x, y, width, height);

    ofNoFill();
    ofSetColor(BUTTON_BORDER_COLOR_R, BUTTON_BORDER_COLOR_G, BUTTON_BORDER_COLOR_B, opacity);
    ofRect(x, y, width, height);

    float textWidth = 8.0f * displayText[active].length();
    float remainX = (width - textWidth)/2;

    float textHeight = 14.0f;
    float remainY = (height - textHeight)/2.0f + (textHeight/2.0f);

    ofSetColor(BUTTON_TEXT_COLOR_R, BUTTON_TEXT_COLOR_G, BUTTON_TEXT_COLOR_B, opacity);
    ofDrawBitmapString(displayText[active], x + remainX, y + remainY);
}

int ButtonToggle::fromString(const std::string& s)
{
    std::istringstream stream (s);
    int t;
    stream >> t;
    return t;
}

void ButtonToggle::draw(string s)
{

    ofFill();
    ofSetColor(fromString(s));

    float pctActive = ofMap(pct, 0.0, 1.5, 0.0, 110.0);
    ofRect(x, y, width, height);
    if (pct>.1)
    {
        ofPushStyle();
        ofSetLineWidth(4);
        ofNoFill();

        ofRect(x, y, width, height);
        ofPopStyle();
    }
}

float ButtonToggle::getY()
{
    return y;
}

float ButtonToggle::getX()
{
    return x;
}

