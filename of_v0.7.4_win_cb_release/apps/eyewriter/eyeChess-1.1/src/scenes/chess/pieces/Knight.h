#ifndef KNIGHT_H_INCLUDED
#define KNIGHT_H_INCLUDED

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
    Knight( int file, int row, bool isWhite) : ChessPiece(file, row, isWhite)
    {
        if(isWhite)
            imagePath = "images/KnightW.png";
        else
            imagePath = "images/KnightB.png";
    }
    bool canMove( int** places, int newFile, int newRow);
};

#endif // KNIGHT_H_INCLUDED
