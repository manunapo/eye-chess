#import "Rook.h"

bool Rook::canMove( int** places, int newFile, int newRow)
{
    bool isVerticalOrHorizontal = isRoadVertical(newFile, newRow) || isRoadHorizontal(newFile, newRow);
    bool isFreeRoad = isFreeRoadTo(places, newFile, newRow);
    return isVerticalOrHorizontal && isFreeRoad;
}
