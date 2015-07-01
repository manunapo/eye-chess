#include "MachineChessMapper.h"

MachineChessMapper::MachineChessMapper(FeedbackHandler* fh)
{
    float file = 12.5;
    float row = 12.5;
    for( int i = 0; i < 8; i++)
    {
        for( int j = 0; j < 8; j++)
        {
            BoxToCoord[i][j] = new Coord( file + 25 * j, row + 25 * i);
        }
    }

    CommHandler* cm = new CommHandler(fh);
    cm->startTransmission();
    ops = cm->getOperations();
}

void MachineChessMapper::movePieceTo( int f, int r, int newF, int newR)
{
    //down magnet
    ops->addOperation(new Operation('Z'));

    ops->addOperation(new Operation('C', BoxToCoord[f][r]->x));
    ops->addOperation(new Operation('C', BoxToCoord[f][r]->y));

    //up magnet
    ops->addOperation(new Operation('A'));

    ops->addOperation(new Operation('C', BoxToCoord[newF][newR]->x));
    ops->addOperation(new Operation('C', BoxToCoord[newF][newR]->y));

    cout << f << r << newF << newR;
    ops->setLastMove(f,r,newF,newR);

    //start sensig
    ops->addOperation(new Operation('B'));

}

void MachineChessMapper::endGame()
{
    ops->addOperation(new Operation('T'));
}
