#pragma once
#include <string>
#include <cmath>
#include <iostream>

using namespace std;
class ChessPiece
{
protected:
    int myFile;
    int myRow;
    bool white;
    string imagePath = "images/Free.png";

public:
    ChessPiece( int file, int row, bool isWhite);

    //do no check if the box is available, that is responsability of the board.
    virtual bool canMove( int** places, int newFile, int newRow){}

    //The road only can be vertical, horizontal or diagonal.
    bool isFreeRoadTo( int** places, int newFile, int newRow);
    bool isRoadVertical(int newFile, int newRow);
    bool isRoadHorizontal(int newFile, int newRow);
    bool isRoadDiagonal(int newFile, int newRow);

    void updateBox( int newF, int newR);
    bool isWhite();
    string getImage();
};
