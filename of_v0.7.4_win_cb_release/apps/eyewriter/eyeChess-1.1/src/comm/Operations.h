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
    int coords[4] = {0,0,0,0};

public:
    Operations();
    void addOperation(Operation* op);
    Operation* getNextOperation();
    bool hasOperation();
    void setLastMove(int f, int r, int tf, int tr);
    void getLastMove(int moveAux[4]);
};

#endif // OPERATIONS_H_INCLUDED
