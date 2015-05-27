//
//  testingScene.h
//  temptTracker021
//
//  Created by joseph saavedra on 1/6/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "BaseScene.h"
#include "ButtonTrigger.h"
#include "ButtonToggle.h"


class TestingScene : public BaseScene
{
public:

    void setup();
    void update(float eyeX, float eyeY);
    void draw();
    void mouseDragged(int x, int y, int button);

    ButtonTrigger       BTrig;
    ButtonToggle        BTog;

    ButtonTrigger       decSensitivity;
    ButtonTrigger       incSensitivity;

    float               currSensitivity;
};
