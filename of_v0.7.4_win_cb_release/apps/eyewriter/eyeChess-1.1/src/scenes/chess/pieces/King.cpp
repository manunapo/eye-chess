#import "King.h"

bool King::canMove( int** places, int newFile, int newRow)
{
    bool oneStep = abs(myFile - newFile) == 1 || abs(myRow - newRow) == 1;
    return oneStep;
}
