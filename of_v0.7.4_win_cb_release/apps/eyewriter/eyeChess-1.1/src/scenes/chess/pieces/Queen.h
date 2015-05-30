#ifndef QUEEN_H_INCLUDED
#define QUEEN_H_INCLUDED

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
    Queen( int file, int row, bool isWhite) : ChessPiece( file, row, isWhite)
    {
        if(isWhite)
            imagePath = "images/QueenW.png";
        else
            imagePath = "images/QueenB.png";
    }
    bool canMove( int** places, int newFile, int newRow);
};

#endif // QUEEN_H_INCLUDED
