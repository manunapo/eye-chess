#include "Operations.h"

Operations::Operations()
{
}

void Operations::addOperation(Operation* op)
{
    operations.push(op);
}

Operation* Operations::getNextOperation()
{
    if(!operations.empty())
    {
        Operation* toR = operations.front();
        operations.pop();
        return toR;
    }
}

bool Operations::hasOperation()
{
    return !operations.empty();
}

void Operations::setLastMove(int f, int r, int tf, int tr)
{
    coords[0] = f;
    coords[1] = r;
    coords[2] = tf;
    coords[3] = tr;
}

void Operations::getLastMove(int moveAux[4])
{
        moveAux[0] = coords[0];
        moveAux[1] = coords[1];
        moveAux[2] = coords[2];
        moveAux[3] = coords[3];
}
