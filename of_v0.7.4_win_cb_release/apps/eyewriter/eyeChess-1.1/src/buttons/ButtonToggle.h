/*
 *  buttonToggle.h
 *  openFrameworks
 *
 *  Created by theo on 17/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ButtonRect.h"
#include "Defines.h"

class ButtonToggle : public ButtonRect
{

public:

    ButtonToggle();
    void    setMaxCounter(float nCounter);
    void    setup( string onName, string offName,  bool startsActive, float xIn, float yIn, float w, float h);
    bool    update(float xIn, float yIn);
    bool    getState();
    void    draw(float opacity = 255);
    void    draw(string s);
    int     fromString(const std::string& s);
    float   getY();
    float   getX();

    void    relocate(float newX, float newY);

    float   timeDiff;
    float   timeStamp;
    bool    firstTrigger;
    bool    turned;
    float   pct;

    float   preTime;
    float   counter;
    bool    hasLeft;
    float   maxCount;
    string  displayText[2];
    bool    active;

};
