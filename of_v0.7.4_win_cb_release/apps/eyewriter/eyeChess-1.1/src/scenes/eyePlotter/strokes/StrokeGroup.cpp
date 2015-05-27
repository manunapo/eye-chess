/*
 *  strokeGroup.cpp
 *  openFrameworks
 *
 *  Created by theo on 17/08/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "strokeGroup.h"

StrokeGroup::StrokeGroup()
{
    newStrokeOnNext = true;
}

void StrokeGroup::begin()
{
    newStrokeOnNext = true;
}

void StrokeGroup::addPoint(float x, float y)
{
    if(strokes.size() == 0)
    {
        newStrokeOnNext = true;
    }

    if( newStrokeOnNext )
    {
        strokes.push_back(SpecialPolyline());
        newStrokeOnNext = false;
    }
    strokes.back().addVertex(x, y);
}

void StrokeGroup::nextStroke()
{
    newStrokeOnNext = true;
}

void StrokeGroup::clear()
{
    strokes.clear();
}

ofPoint StrokeGroup::getLastPoint()
{
    if( hasPoints() )
    {
        return strokes.back().getVertices().back();
    }
}

int StrokeGroup::getLastStrokeNumPoints()
{
    int num = 0;
    if( strokes.size() )
    {
        return strokes.back().getVertices().size();
    }
    return num;
}

int StrokeGroup::getTotalNumPoints()
{
    int num = 0;
    for(int k = 0; k < strokes.size(); k++)
    {
        num += strokes[k].getVertices().size();
    }
    return num;
}

bool StrokeGroup::hasPoints()
{
    return (strokes.size() && strokes.back().getVertices().size() );
}

void StrokeGroup::draw()
{
    for(int i = 0; i < strokes.size(); i++)
    {
        strokes[i].draw();
    }
}

int StrokeGroup::size()
{
    return strokes.size();
}

void StrokeGroup::clearLast()
{
    strokes.back().clear();
}

ofPoint StrokeGroup::StrokeGroup::getFirstVertexOfLastStroke()
{
    return strokes.back().getVertices()[0];
}

bool StrokeGroup::isNewStrokeOnNext()
{
    return newStrokeOnNext;
}
