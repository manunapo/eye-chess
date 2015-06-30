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
#include "FeedbackHandler.h"

class CommHandler
{
private:
    Operations* operations;
    Serial* SP;
    FeedbackHandler* FH;

    DWORD checkThreadId;
    HANDLE checkThreadHandle;

public:
    CommHandler(FeedbackHandler* fh);
    void startTransmission();
    void stopTransmission();
    Operations* getOperations();
};

class Wrapper
{
public:
    Serial* SP;
    Operations* Ops;
    FeedbackHandler* FH;

    Wrapper(Serial* sp, Operations* ops, FeedbackHandler* fh)
    {
        SP = sp;
        Ops = ops;
        FH = fh;
    }
};
