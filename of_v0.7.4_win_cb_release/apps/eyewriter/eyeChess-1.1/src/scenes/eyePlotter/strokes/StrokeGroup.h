/*
 *  strokeGroup.h
 *  openFrameworks
 *
 *  Created by theo on 17/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "SpecialPolyline.h"


class StrokeGroup
{
protected:
    bool newStrokeOnNext;
    vector <SpecialPolyline> strokes;

public:
    StrokeGroup();
    void begin();
    void addPoint(float x, float y);
    void nextStroke();
    void clear();
    ofPoint getLastPoint();
    int getLastStrokeNumPoints();
    int getTotalNumPoints();
    bool hasPoints();
    void draw();
    int size();
    void clearLast();
    ofPoint getFirstVertexOfLastStroke();
    bool isNewStrokeOnNext();
};
