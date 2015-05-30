#import "Bishop.h"

bool Bishop::canMove( int** places, int newFile, int newRow)
{
    bool isDiagonal = isRoadDiagonal(newFile, newRow);
    bool isFreeRoad = isFreeRoadTo(places, newFile, newRow);
    return isDiagonal && isFreeRoad;
}
