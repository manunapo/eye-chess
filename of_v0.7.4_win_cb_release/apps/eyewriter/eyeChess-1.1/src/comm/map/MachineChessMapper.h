#include "comm/CommHandler.h"

class Coord
{
public:
    float x;
    float y;

    Coord( float nx, float ny)
    {
        x = nx;
        y = ny;
    }
};

class MachineChessMapper
{
private:
    //Chess box mapping: each position in the matrix has a hardware  coordinate.
    Coord* BoxToCoord[8][8];
    Operations* ops;

public:
    MachineChessMapper();

    void movePieceTo( int f, int r, int newF, int newR);
};
