#include "CommHandler.h"

CommHandler::CommHandler()
{
    SP = new Serial("COM3");
    operations = new Operations();

    if (SP->IsConnected())
		printf("We're connected \n");

}

DWORD WINAPI check(LPVOID lpParameter)
{
    Wrapper* wrapper = (Wrapper*) lpParameter;
    Serial* SP = (Serial*) wrapper->SP;
    Operations* Ops = (Operations*) wrapper->Ops;

    char data = 'S';
    int dataLength = sizeof(char);
    SP->WriteData( &data, dataLength);

	int readResult = 0;

    while(true)
    {
        readResult = SP->ReadData( &data,dataLength);
        if(readResult == -1)
        {
            printf("-1 means no data available \n");
        }
        else
        {
            printf("Data read %c \n",data);
            if(Ops->hasOperation())
            {
                Operation* op = Ops->getNextOperation();
                char data = op->getType();
                if( data != 'C')
                {
                    SP->WriteData( &data, dataLength);
                }
                else
                {
                    int x = op->getX() * 10000;
                    int y = op->getY() * 10000;
                    stringstream ss;
                    ss << x;
                    string sx = ss.str();
                    ss << y;
                    string sy = ss.str();
                }
            }
        }
        Sleep(500);
    }
}

void CommHandler::startTransmission()
{
	Wrapper* wrapped = new Wrapper(SP, operations);
    checkThreadHandle = CreateThread( 0, 0, check, wrapped, 0, &checkThreadId);

    Operation* op = new Operation( 'C', 50, 50);
    operations->addOperation(op);
}

void CommHandler::stopTransmission()
{
    TerminateThread( checkThreadHandle, 1);
}
