#include "SpecialPolyline.h"

SpecialPolyline::SpecialPolyline()
{
    filled = false;
    closed = false;
}
void SpecialPolyline::setFilled( bool state)
{
    filled = state;
}

void SpecialPolyline::setClosed( bool state)
{
    closed = state;
}

bool SpecialPolyline::isFilled()
{
    return filled;
}

bool SpecialPolyline::isClosed()
{
    return closed;
}

void SpecialPolyline::draw()
{
    ofBeginShape();
    for( int i = 0; i < getVertices().size(); i++) {
        ofVertex(getVertices().at(i).x, getVertices().at(i).y);
    }
    ofNoFill();
    ofEndShape();
    ofFill();
    if( getVertices().size() )
    {
        ofCircle(getVertices().back().x, getVertices().back().y, 4);
    }
}

