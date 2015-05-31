#ifndef PAWN_H_INCLUDED
#define PAWN_H_INCLUDED

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
protected:
    bool isFirstMove;
public:
    Pawn(int file, int row, bool isWhite) : ChessPiece( file, row, isWhite)
    {
        if(isWhite)
            imagePath = "images/PawnW.png";
        else
            imagePath = "images/PawnB.png";
        isFirstMove = true;
    }
    bool canMove( int** places, int newFile, int newRow);
};

#endif // PAWN_H_INCLUDED
