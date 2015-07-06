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
    lastY = 0;
}

void MachineChessMapper::movePieceTo( bool isKnight, int f, int r, int newF, int newR)
{
    //down magnet
    ops->addOperation(new Operation('Z'));

    ops->addOperation(new Operation('C', BoxToCoord[f][r]->x));
    ops->addOperation(new Operation('C', lastY));

    ops->addOperation(new Operation('C', BoxToCoord[f][r]->x));
    ops->addOperation(new Operation('C', BoxToCoord[f][r]->y));

    //up magnet
    ops->addOperation(new Operation('A'));

    if( isKnight)
    {
        float x1 = BoxToCoord[f][r]->x;
        float x2 = BoxToCoord[newF][newR]->x;

        float y1 = BoxToCoord[f][r]->y;
        float y2 = BoxToCoord[newF][newR]->y;

        float dY = y1 - y2;
        float dX = x1 - x2;

        if(dY < 0) dY = dY * -1;
        if(dX < 0) dX = dX * -1;

        if( dX < dY)
        {
            float middleX = 0;
            if( x2 < x1)
                middleX = x1 - 12.5;
            else
                middleX = x1 + 12.5;

            ops->addOperation(new Operation('C', middleX));
            ops->addOperation(new Operation('C', y1));

            ops->addOperation(new Operation('C', middleX));
            ops->addOperation(new Operation('C', y2));
        }
        else
        {
            float middleY = 0;
            if( y2 < y1)
                middleY = y1 - 12.5;
            else
                middleY = y1 + 12.5;

            ops->addOperation(new Operation('C', x1));
            ops->addOperation(new Operation('C', middleY));

            ops->addOperation(new Operation('C', x2));
            ops->addOperation(new Operation('C', middleY));
        }

    }

    ops->addOperation(new Operation('C', BoxToCoord[newF][newR]->x));
    ops->addOperation(new Operation('C', BoxToCoord[newF][newR]->y));

    //down magnet
    ops->addOperation(new Operation('Z'));

    lastY = BoxToCoord[newF][newR]->y;

    ops->setLastMove(f,r,newF,newR);

    //start sensig
    ops->addOperation(new Operation('B'));

}

void MachineChessMapper::endGame()
{
    ops->addOperation(new Operation('T'));
}
