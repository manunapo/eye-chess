#include "comm/CommHandler.h"
#include "comm/FeedbackHandler.h"

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
    float lastY;

public:
    MachineChessMapper(FeedbackHandler* fh);
    void movePieceTo(bool isKnight, int f, int r, int newF, int newR);
    void endGame();
};
