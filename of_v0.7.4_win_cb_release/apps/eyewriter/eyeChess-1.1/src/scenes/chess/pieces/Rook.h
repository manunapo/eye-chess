#ifndef ROOK_H_INCLUDED
#define ROOK_H_INCLUDED

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
    Rook( int file, int row, bool isWhite) : ChessPiece( file, row, isWhite)
    {
        if(isWhite)
            imagePath = "images/RookW.png";
        else
            imagePath = "images/RookB.png";
    }
};

#endif // ROOK_H_INCLUDED
