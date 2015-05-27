//
//  testingScene.cpp
//  temptTracker021
//
//  Created by joseph saavedra on 1/6/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

//#include <iostream>
#include "TestingScene.h"
#include "TestApp.h"

void TestingScene::setup()
{

    BTrig.setup("catch me!", 50, 400,180,180);
    //BTrig.setMaxCounter(1.0); //button sensitivity

    BTog.setup("toggle me off","toggle me on",false,250,250,180,180);

    incSensitivity.setup("increase", ofGetWidth()-110, 30,100,100);
    decSensitivity.setup("decrease", ofGetWidth()-220, 30,100,100);

    currSensitivity = ((TestApp *)ofGetAppPtr())->buttonSensitivity;
}


void TestingScene::update(float eyeX, float eyeY)
{
    if (BTrig.update(eyeX, eyeY))
    {
        BTrig.x = ofRandom(180,ofGetWidth()-180);
        BTrig.y = ofRandom(180,ofGetHeight()-180);
    }
    else if (BTog.update(eyeX, eyeY))
    {
        BTog.x = ofRandom(180,ofGetWidth()-180);
        BTog.y = ofRandom(180,ofGetHeight()-180);
    }
    else if (incSensitivity.update(eyeX, eyeY))
    {
        currSensitivity += 0.5;
        ((TestApp *)ofGetAppPtr())->buttonSensitivity = currSensitivity;
    }
    else if (decSensitivity.update(eyeX, eyeY))
    {
        currSensitivity -= 0.5;
        ((TestApp *)ofGetAppPtr())->buttonSensitivity = currSensitivity;
    }
}


void TestingScene::draw()
{

    ofSetColor(255, 255, 255);
    ofDrawBitmapString("current sensitivity: " + ofToString(((TestApp *)ofGetAppPtr())->buttonSensitivity),
                       ofGetWidth()-205, 150);
    ofDrawBitmapString("set button sensitivity", ofGetWidth()-205, 20);

    BTrig.draw();
    BTog.draw();
    decSensitivity.draw();
    incSensitivity.draw();
}

void TestingScene::mouseDragged(int x, int y, int button)
{


}
