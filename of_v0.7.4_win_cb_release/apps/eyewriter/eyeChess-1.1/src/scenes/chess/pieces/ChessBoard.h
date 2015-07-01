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
#include "scenes/chess/ButtonMatrix.h"

class FeedbackHandler;

class ChessBoard
{
protected:
    ChessPiece* board[8][8];
    int firstSelectedF;
    int firstSelectedR;
    int secondSelectedF;
    int secondSelectedR;

    // true if computer has turn, false if human has.
    bool turn;

    MachineChessMapper* mapper;
    ButtonMatrix* buttons;

public:
    ChessBoard();
    bool isFree(int f, int r);
    string getImage(int f, int r);
    void boxSelected(ButtonMatrix* bts,int f, int r);
    void endGame();
    void moveFromTo(int fromFile, int fromRow, int toFile, int toRow);
    bool hasTurn();

    //return a matriz with
    //  .0 if the box is free
    //  .1 if the box has a white piece
    //  .2 if the box has a black piece
    int** getPlacesMatrix();
};

