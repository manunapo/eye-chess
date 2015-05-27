#ifndef KING_H_INCLUDED
#define KING_H_INCLUDED

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
    King(int file, int row, bool isWhite) : ChessPiece( file, row, isWhite)
    {
        if(isWhite)
            imagePath = "images/KingW.png";
        else
            imagePath = "images/KingB.png";
    }
};

#endif // KING_H_INCLUDED
