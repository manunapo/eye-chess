#include "Operation.h"

Operation::Operation(char theType)
{
    type = theType;
    x = 0;
    y = 0;
}

void Operation::setCoords(float newX, float newY)
{
    x = newX;
    y = newY;
}

char Operation::getType()
{
    return type;
}

float Operation::getX()
{
    return x;
}

float Operation::getY()
{
    return y;
}
