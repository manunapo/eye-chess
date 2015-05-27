#include "CommHandler.h"

CommHandler::CommHandler()
{
    SP = new Serial("COM4");
    operations = new Operations();

    if (SP->IsConnected())
		printf("We're connected \n");

}

DWORD WINAPI check(LPVOID lpParameter)
{
    char data = 'S';
	int dataLength = 2;
	int readResult = 0;
    while(true)
    {
        Wrapper* wrapper = (Wrapper*) lpParameter;
        Serial* SP = (Serial*) wrapper->SP;
        Operations* Ops = (Operations*) wrapper->Ops;

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
                char data = Ops->getNextOperation()->getType();
                SP->WriteData( &data, dataLength);
            }
        }
        Sleep(500);
    }
}



void CommHandler::startTransmission()
{
    char data = 'S';
	int dataLength = 1;
	int readResult = 0;

	SP->WriteData( &data, dataLength);
	Wrapper* wrapped = new Wrapper(SP, operations);

    checkThreadHandle = CreateThread( 0, 0, check, wrapped, 0, &checkThreadId);
    data = 'Z';
    Operation* op = new Operation(data);
    operations->addOperation(op);
}

void CommHandler::stopTransmission()
{
    TerminateThread( checkThreadHandle, 1);
}
