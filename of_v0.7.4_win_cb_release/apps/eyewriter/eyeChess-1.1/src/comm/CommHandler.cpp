#include "CommHandler.h"

CommHandler::CommHandler(FeedbackHandler* fh)
{
    SP = new Serial("COM5");
    operations = new Operations();
    FH = fh;

    if (SP->IsConnected())
		printf("We're connected \n");

}

DWORD WINAPI check(LPVOID lpParameter)
{
    Wrapper* wrapper = (Wrapper*) lpParameter;
    Serial* SP = (Serial*) wrapper->SP;
    Operations* Ops = (Operations*) wrapper->Ops;
    FeedbackHandler* f = (FeedbackHandler*) wrapper->FH;

    int dataLength = sizeof(char);

    char data = 'S';
    SP->WriteData( &data, dataLength);
	int readResult = 0;
	bool sendY = false;
    Operation* op;

    bool sensing = false;
    int oponentMove[4];
    int pos = 0;

    while(true)
    {
        readResult = SP->ReadData( &data,dataLength);
        while(readResult == -1)
        {
            Sleep(300);
            cout << " no data " << "\n";
            readResult = SP->ReadData( &data,dataLength);
        }
        if(sensing)
        {

            if((data != '@') && (data != '%'))
            {
                oponentMove[pos++] = (int) data;
                cout << " move: " << oponentMove[pos-1] << "\n";
            }
            if( pos == 4)
            {
                f->informMove( oponentMove[0], oponentMove[1], oponentMove[2], oponentMove[3]);
                cout << "informing \n";
                pos = 0;
                sensing = false;
            }
        }
        else
        {
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
                    if( data == 'B')
                    {
                        stringstream ss, ss1, ss2, ss3;

                        int moveAux[4] = {0,0,0,0};
                        Ops->getLastMove(moveAux);

                        ss << moveAux[0];
                        string sn = ss.str();
                        cout << "string: " << sn << "\n";
                        data = sn.at(0);
                        SP->WriteData( &data, dataLength);

                        ss1 << moveAux[1];
                        sn = ss1.str();
                        cout << "string: " << sn << "\n";
                        data = sn.at(0);
                        SP->WriteData( &data, dataLength);

                        ss2 << moveAux[2];
                        sn = ss2.str();
                        cout << "string: " << sn << "\n";
                        data = sn.at(0);
                        SP->WriteData( &data, dataLength);

                        ss3 << moveAux[3];
                        sn = ss3.str();
                        cout << "string: " << sn << "\n";
                        data = sn.at(0);
                        SP->WriteData( &data, dataLength);

                        sensing = true;
                    }
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
}

void CommHandler::startTransmission()
{
	Wrapper* wrapped = new Wrapper(SP, operations, FH);
    checkThreadHandle = CreateThread( 0, 0, check, wrapped, 0, &checkThreadId);
}

void CommHandler::stopTransmission()
{
    TerminateThread( checkThreadHandle, 1);
}

Operations* CommHandler::getOperations()
{
    return operations;
}
