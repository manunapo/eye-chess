#include "CommHandler.h"

CommHandler::CommHandler()
{
    SP = new Serial("COM5");
    operations = new Operations();

    if (SP->IsConnected())
		printf("We're connected \n");

}

DWORD WINAPI check(LPVOID lpParameter)
{
    Wrapper* wrapper = (Wrapper*) lpParameter;
    Serial* SP = (Serial*) wrapper->SP;
    Operations* Ops = (Operations*) wrapper->Ops;

    int dataLength = sizeof(char);

    char data = 'S';
    SP->WriteData( &data, dataLength);
	int readResult = 0;
	bool sendY = false;
    Operation* op;

    while(true)
    {
        readResult = SP->ReadData( &data,dataLength);
        while(readResult == -1)
        {
            Sleep(300);
            cout << " no data " << "\n";
            readResult = SP->ReadData( &data,dataLength);
        }
        while(!Ops->hasOperation())
        {
            Sleep(300);
            cout << " no operation " << "\n";
        }
        if(Ops->hasOperation())
        {
            op = Ops->getNextOperation();
            data  = op->getType();
            if( data != 'C')
            {
                SP->WriteData( &data, dataLength);
            }
            else
            {
                int n = op->getN() * 10000;
                stringstream ss;
                ss << n;
                string sn = ss.str();
                for( int i = 0; i < sn.length(); i++)
                {
                    SP->WriteData( &sn.at(i), dataLength);
                    cout << "send: " << sn.at(i) << "\n";
                }
                data = '.';
                SP->WriteData( &data, dataLength);
                cout << "send: " << data << "\n";
            }
        }

    }
}

void CommHandler::startTransmission()
{
	Wrapper* wrapped = new Wrapper(SP, operations);
    checkThreadHandle = CreateThread( 0, 0, check, wrapped, 0, &checkThreadId);
/*
    Operation* op = new Operation( 'Z');
    operations->addOperation(op);
    op = new Operation( 'C', 0);
    operations->addOperation(op);
    op = new Operation( 'C', 0);
    operations->addOperation(op);
/*
    Operation* op = new Operation( 'Z');
    operations->addOperation(op);

    op = new Operation( 'C', 25);
    operations->addOperation(op);
    op = new Operation( 'C', 0);
    operations->addOperation(op);

    op = new Operation( 'C', 25);
    operations->addOperation(op);
    op = new Operation( 'C', 200);
    operations->addOperation(op);

    op = new Operation( 'C', 50);
    operations->addOperation(op);
    op = new Operation( 'C', 200);
    operations->addOperation(op);

    op = new Operation( 'C', 50);
    operations->addOperation(op);
    op = new Operation( 'C', 0);
    operations->addOperation(op);
    //----
    op = new Operation( 'C', 75);
    operations->addOperation(op);
    op = new Operation( 'C', 0);
    operations->addOperation(op);

    op = new Operation( 'C', 75);
    operations->addOperation(op);
    op = new Operation( 'C', 200);
    operations->addOperation(op);

    op = new Operation( 'C', 100);
    operations->addOperation(op);
    op = new Operation( 'C', 200);
    operations->addOperation(op);

    op = new Operation( 'C', 100);
    operations->addOperation(op);
    op = new Operation( 'C', 0);
    operations->addOperation(op);
    //--
    op = new Operation( 'C', 125);
    operations->addOperation(op);
    op = new Operation( 'C', 0);
    operations->addOperation(op);

    op = new Operation( 'C', 125);
    operations->addOperation(op);
    op = new Operation( 'C', 200);
    operations->addOperation(op);

    op = new Operation( 'C', 150);
    operations->addOperation(op);
    op = new Operation( 'C', 200);
    operations->addOperation(op);

    op = new Operation( 'C', 150);
    operations->addOperation(op);
    op = new Operation( 'C', 0);
    operations->addOperation(op);
    //--
    op = new Operation( 'C', 175);
    operations->addOperation(op);
    op = new Operation( 'C', 0);
    operations->addOperation(op);

    op = new Operation( 'C', 175);
    operations->addOperation(op);
    op = new Operation( 'C', 200);
    operations->addOperation(op);

    op = new Operation( 'C', 200);
    operations->addOperation(op);
    op = new Operation( 'C', 200);
    operations->addOperation(op);
    //--

    op = new Operation( 'A');
    operations->addOperation(op);*/
}

void CommHandler::stopTransmission()
{
    TerminateThread( checkThreadHandle, 1);
}

Operations* CommHandler::getOperations()
{
    return operations;
}
