#import "Queen.h"

bool Queen::canMove( int** places, int newFile, int newRow)
{
    bool isFreeRoad = isFreeRoadTo(places, newFile, newRow);
    return isFreeRoad;
}
