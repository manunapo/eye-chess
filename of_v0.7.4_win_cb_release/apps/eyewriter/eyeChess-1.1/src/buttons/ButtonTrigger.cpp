/*
 *  buttonTrigger.cpp
 *  openFrameworks
 *
 *  Created by theo on 17/08/2009.
 *  Modify by Manuel Napoli 26/06/2015
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ButtonTrigger.h"
#include "TestApp.h"

ButtonTrigger::ButtonTrigger()
{

    active  = false;
    hasLeft = true;
    counter = 0.0f;
    pct = 0.0f;
    allowRetrigger = false;
    numTriggers = 0;
    bFlash = false;
    bHasFont = false;
    selected = false;
}


void ButtonTrigger::setDisplayFont(ofTrueTypeFont * fontIn)
{
    font = fontIn;
    bHasFont = true;
}

void ButtonTrigger::setRetrigger(bool retrigger)
{
    allowRetrigger = retrigger;
}

void ButtonTrigger::setMaxCounter(float nCounter)
{
    maxCount = nCounter;
}

void ButtonTrigger::setup( string onName, float xIn, float yIn, float w, float h )
{
    displayText = onName;

    x		= xIn;
    y		= yIn;
    width	= w;
    height	= h;
    numTriggers = 0;
    flashLength = 0.2;

    maxCount = ((TestApp *)ofGetAppPtr())->buttonSensitivity;
}

void ButtonTrigger::setup( string onName, string texture, float xIn, float yIn, float w, float h )
{
    displayText = onName;

    x		= xIn;
    y		= yIn;
    width	= w;
    height	= h;
    numTriggers = 0;
    flashLength = 0.2;
    imagePath = texture;
    maxCount = ((TestApp *)ofGetAppPtr())->buttonSensitivity;
}

void ButtonTrigger::relocate(float newX, float newY)
{
    x = newX;
    y = newY;
}

int ButtonTrigger::getNumTriggers()
{
    if( allowRetrigger )
    {
        return numTriggers;
    }
    else
    {
        return 0;
    }
}

void ButtonTrigger::setFlashLength(float timeF)
{
    flashLength = MAX(0, timeF);
}

bool ButtonTrigger::update(float xIn, float yIn)
{
    bool changed = false;

    float currentTime = ofGetElapsedTimef();

    if( inRect(xIn, yIn) )
    {
        if(!active)
        {
            if (firstTrigger)
            {
                timeStamp = currentTime;
                active = true;
                firstTrigger = false;
            }
        }

        else
        {
            float timeDiff = currentTime - timeStamp;
            pct = timeDiff/maxCount;

            if (timeDiff >= maxCount)
            {
                changed = true;
                if(allowRetrigger)
                {
                    cout << "retrigger" << endl;
                    active = true;
                    timeStamp = currentTime;
                    bFlash = true;
                    flashTill = currentTime + flashLength;
                }
                else
                {
                    active = false;
                    timeStamp = currentTime;
                    bFlash = true;
                    flashTill = currentTime + flashLength;
                    pct = 0.0f;
                }
            }
        }
    }
    else   //mouse not inRect
    {
        active = false;
        pct = 0;
        firstTrigger = true;
    }

    if( bFlash && ofGetElapsedTimef() > flashTill )
    {
        bFlash = false;
    }

    return changed;
}

void ButtonTrigger::updateTexture()
{
    if(imagePath != "")
    {
        ofImage myImage;
        myImage.loadImage(imagePath);
        myImage.draw(x,y,width,height);
    }

}

void ButtonTrigger::changeImage(string path)
{
    imagePath = path;
}

void ButtonTrigger::draw(float opacity)
{
    updateTexture();

    opacity = 50;
    if(selected)
       opacity = 160;

    ofFill();

    float pctActive = ofMap(pct, 0.0, 1.5, 0.0, 110.0);
    if( bFlash)
    {
        ofSetColor( 0, 100, 240, opacity);
    }
    else
    {
        ofSetColor( 60 - pctActive, 120 + pctActive * 2, 180 - pctActive, opacity);
    }


    ofRect( x, y, width, height);


    ofNoFill();
    ofSetColor(BUTTON_BORDER_COLOR_R, BUTTON_BORDER_COLOR_G, BUTTON_BORDER_COLOR_B, opacity);
    ofRect(x, y, width, height);

    if (!bHasFont)
    {
        float textWidth = 8.0f * displayText.length();
        float remainX = (width - textWidth)/2;

        float textHeight = 14.0f;
        float remainY = (height - textHeight)/2.0f + (textHeight/2.0f);

        ofSetColor(BUTTON_TEXT_COLOR_R, BUTTON_TEXT_COLOR_G, BUTTON_TEXT_COLOR_B);
        ofDrawBitmapString(displayText, x + remainX, y + remainY);
    }
    else
    {
        ofRectangle bounds = font->getStringBoundingBox(displayText, 0,0);

        float textWidth = bounds.width;
        float remainX = (width - textWidth)/2;

        float textHeight = bounds.height;
        float remainY = (height - textHeight)/2.0f + (textHeight/2.0f);
        ofSetColor(60, 60, 60);
        font->drawString(displayText, x + remainX, y + remainY);
    }

}

int ButtonTrigger::fromString(const std::string& s)
{
    std::istringstream stream (s);
    int t;
    stream >> t;
    return t;
}

void ButtonTrigger::draw(string s)
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

        if( bFlash)
        {
            ofSetColor(0, 100, 240);
        }
        else
        {
            ofSetColor(120+pctActive*2, 120+pctActive*2, 120 + pctActive*2, 255);
        }

        ofRect(x, y, width, height);
        ofPopStyle();
    }
}

float ButtonTrigger::getY()
{
    return y;
}

float ButtonTrigger::getX()
{
    return x;
}

void ButtonTrigger::select()
{
    selected = !selected;
}
