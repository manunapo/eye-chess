#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <queue>
#include "Operation.h"

using namespace std;

class Operations
{
private:
    queue<Operation*> operations;

public:
    Operations();
    void addOperation(Operation* op);
    Operation* getNextOperation();
    bool hasOperation();
};

#endif // OPERATIONS_H_INCLUDED
