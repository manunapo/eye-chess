#import "Knight.h"

bool Knight::canMove( int** places, int newFile, int newRow)
{
    bool isLMove = (abs(myFile - newFile) == 1) && (abs(myRow - newRow) == 2) || (abs(myFile - newFile) == 2) && (abs(myRow - newRow) == 1);
    return isLMove;
}
