#pragma once
#include <iostream>
#include <string>
#include "ChessPiece.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Pawn.h"
#include "ButtonTrigger.h"
#include "comm/map/MachineChessMapper.h"

using namespace std;
class ChessBoard
{
protected:
    ChessPiece* board[8][8];
    int firstSelectedF;
    int firstSelectedR;
    int secondSelectedF;
    int secondSelectedR;
    MachineChessMapper* mapper;
public:
    ChessBoard();
    bool isFree(int f, int r);
    string getImage(int f, int r);
    void boxSelected(ButtonTrigger buttons[8][8], int f, int r);

    //return a matriz with
    //  .0 if the box is free
    //  .1 if the box has a white piece
    //  .2 if the box has a black piece
    int** getPlacesMatrix();
};
