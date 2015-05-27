#pragma once
#include "ofMain.h"

class SpecialPolyline : public ofPolyline
{
protected:
    bool filled;
    bool closed;

public:
    SpecialPolyline();
    void setFilled( bool state);
    void setClosed( bool state);
    bool isFilled();
    bool isClosed();
    void draw();
};

