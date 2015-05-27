/*
 *  buttonTrigger.h
 *  openFrameworks
 *
 *  Created by theo on 17/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "ofMain.h"
#include "ButtonRect.h"
//#include "trackingManager.h"

class ButtonTrigger : public ButtonRect
{
protected:
    string imagePath = "";

    void    updateTexture();

public:

    ButtonTrigger();
    //~buttonTrigger();

    void    setup();
    void    setup( string onName, float xIn, float yIn, float w, float h );
    void    setup( string onName, string texture, float xIn, float yIn, float w, float h );
    void    setDisplayFont(ofTrueTypeFont * fontIn);
    void    setRetrigger(bool retrigger);
    void    setMaxCounter(float nCounter);
    int     getNumTriggers();
    void    setFlashLength(float timeF);
    bool    update(float xIn, float yIn);

    void    sizeChanged();
    void    draw(float opacity = 255);
    float   getY();
    float   getX();

    void    relocate(float newX, float newY);

    int     fromString(const std::string& s);
    void    draw(string s);
    int     numTriggers;
    bool    firstTrigger;

    float   preTime;
    float   maxCount;
    float   buttonPressTimer;
    float   timeStamp;

    float   flashLength;
    bool    bFlash;
    float   flashTill;

    bool    allowRetrigger;
    float   pct;
    bool    trigger;
    float   counter;
    bool    hasLeft;
    string  displayText;
    bool    active;

    ofTrueTypeFont * font;
    bool    bHasFont;


};
