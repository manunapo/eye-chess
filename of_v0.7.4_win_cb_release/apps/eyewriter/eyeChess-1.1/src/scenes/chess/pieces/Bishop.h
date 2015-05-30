#ifndef BISHOP_H_INCLUDED
#define BISHOP_H_INCLUDED

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(int file, int row, bool isWhite) : ChessPiece( file, row, isWhite)
    {
        if(isWhite)
            imagePath = "images/BishopW.png";
        else
            imagePath = "images/BishopB.png";
    }
    bool canMove( int** places, int newFile, int newRow);
};

#endif // BISHOP_H_INCLUDED
