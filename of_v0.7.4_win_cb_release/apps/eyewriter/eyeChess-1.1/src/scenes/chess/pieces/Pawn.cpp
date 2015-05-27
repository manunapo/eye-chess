#import "Pawn.h"

bool Pawn::canMove( int** places, int newFile, int newRow)
{
    bool toR = false;
    int maxSteps = 1;
    if(isFirstMove)
        maxSteps = 2;

    if((newRow == myRow)&&(abs(newFile-myFile)<=maxSteps))
    {
        toR = true;
    }
    else
    {

    }
    return toR;
}
