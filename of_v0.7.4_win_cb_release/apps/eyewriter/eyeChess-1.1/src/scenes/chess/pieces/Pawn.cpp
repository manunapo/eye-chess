#import "Pawn.h"

bool Pawn::canMove( int** places, int newFile, int newRow)
{
    bool toR = false;
    int maxSteps = 1;
    if(isFirstMove)
    {
        maxSteps = 2;
        isFirstMove = false;
    }
    if(white)
    {
        int aux = newFile - myFile;
        if((newRow == myRow) && (aux <= maxSteps) && (aux > 0))
        {
            if(places[newFile][newRow] == 0)
            {
                toR = true;
            }
        }
        else
        {
            if((aux == 1)&& (newRow-myRow == 1))
            {
                //Diferent colors
                toR = places[newFile][newRow] != places[myFile][myRow];
            }
        }

    }
    else
    {
        int aux = myFile - newFile;
        if((newRow == myRow) && (aux <= maxSteps) && (aux > 0))
        {
            if(places[newFile][newRow] == 0)
            {
                toR = true;
            }
        }
        else
        {
            if((aux == 1) && (myRow - newRow == 1))
            {
                //Diferent colors
                toR = places[newFile][newRow] != places[myFile][myRow];
            }
        }
    }

    return toR;
}
