#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
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
