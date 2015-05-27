#include "ChessPiece.h"

ChessPiece::ChessPiece( int file, int row, bool isWhite)
{
    myFile = file;
    myRow = row;
    white = isWhite;
}

bool ChessPiece::isWhite()
{
    return white;
}

void ChessPiece::updateBox(int newF, int newR)
{
    myFile = newF;
    myRow = newR;
}

string ChessPiece::getImage()
{
    return imagePath;
}
