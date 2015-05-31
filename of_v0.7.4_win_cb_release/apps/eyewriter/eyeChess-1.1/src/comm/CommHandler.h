#pragma once
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <Windows.h>
#include <cstdlib>
#include "serial/SerialClass.h"
#include "Operations.h"

class CommHandler
{
private:
    Operations* operations;
    Serial* SP;
    DWORD checkThreadId;
    HANDLE checkThreadHandle;

public:
    CommHandler();
    void startTransmission();
    void stopTransmission();
    Operations* getOperations();
};

class Wrapper
{
public:
    Serial* SP;
    Operations* Ops;
    Wrapper(Serial* sp, Operations* ops)
    {
        SP = sp;
        Ops = ops;
    }
};
