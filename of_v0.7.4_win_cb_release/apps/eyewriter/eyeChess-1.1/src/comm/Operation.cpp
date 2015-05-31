#include "Operation.h"

Operation::Operation(char theType)
{
    type = theType;
    number = 0;
}

Operation::Operation(char theType, float nn)
{
    type = theType;
    number = nn;
}

void Operation::setCoords(float newN)
{
    number = newN;
}

char Operation::getType()
{
    return type;
}

float Operation::getN()
{
    return number;
}
