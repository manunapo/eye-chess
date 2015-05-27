/*
 *  drawingScene.h
 *  openFrameworks
 *
 *  Created by theo on 20/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "strokeGroup.h"
#include "buttonStateManager.h"
#include "buttonState.h"

#include "ButtonRect.h"
#include "ButtonToggle.h"
#include "ButtonTrigger.h"

#include "ofxXmlSettings.h"

#include "BaseScene.h"
#include "StrokeGroup.h"
#include "comm/Operations.h"

#include <cmath>

class DrawingScene : public BaseScene
{
private:
    void makeNewStroke();
    void makeFillOutline();
    void makeCloseOutline();
    void relocateButtons();

protected:
    ButtonState	testState;
    ButtonStateManager button;

    ButtonTrigger nextStroke;
    ButtonToggle pause;
    ButtonTrigger closeOutline;
    ButtonTrigger fillOutline;

    bool bCurve;

    int	count;
    string preFix;

    ofxXmlSettings saveSettings;
    ofxXmlSettings settings;

    float tagBeginTime;
    bool bDrawing;

    float lastX;
    float lastY;

    StrokeGroup strokeGroup;

    bool isClosurePoint;
    ofPoint closurePoint;

public:
    void setup();
    void update(float mouseX, float mouseY);
    void draw();

};

