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

bool ChessPiece::isRoadVertical(int newFile, int newRow)
{
    return myRow == newRow;
}

bool ChessPiece::isRoadHorizontal(int newFile, int newRow)
{
    return myFile == newFile;
}

bool ChessPiece::isRoadDiagonal(int newFile, int newRow)
{
    return (abs(myFile - newFile) == abs(myRow - newRow));
}

bool ChessPiece::isFreeRoadTo( int** places, int newFile, int newRow)
{
    bool is = true;
    bool isVertical = isRoadVertical( newFile, newRow);
    bool isHorizontal = isRoadHorizontal( newFile, newRow);
    bool isDiagonal = isRoadDiagonal( newFile, newRow);
    is = isVertical || isHorizontal || isDiagonal;
    if(isVertical)
    {
        int startF = myFile + 1;
        int endF = newFile;
        if( myFile > newFile)
        {
            startF = newFile + 1;
            endF = myFile;
        }
        for(int i = startF; is && i < endF; i ++)
        {
            is = places[i][newRow] == 0;
        }
    }
    if(isHorizontal)
    {
        int startR = myRow + 1;
        int endR = newRow;
        if( myRow > newRow)
        {
            startR = newRow + 1;
            endR = myRow;
        }
        for(int i = startR; is && i < endR; i ++)
        {
            is = places[newFile][i] == 0;
        }
    }
    if(isDiagonal)
    {
        bool bothSmaller = ((myFile < newFile) && (myRow < newRow)) || ((myFile > newFile) && (myRow > newRow));
        int startF = myFile;
        int startR = myRow;
        if(myRow > newRow)
        {
            startF = newFile;
            startR = newRow;
        }
        if(bothSmaller)
        {
            for(int i = 1; is && i < abs(myRow-newRow); i++)
            {
                is = places[startF + i][startR + i] == 0;
            }
        }
        else
        {
            for(int i = 1; is && i < abs(myRow-newRow); i++)
            {
                is = places[startF - i][startR + i] == 0;
            }
        }

    }
    return is;
}
