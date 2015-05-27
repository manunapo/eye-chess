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
