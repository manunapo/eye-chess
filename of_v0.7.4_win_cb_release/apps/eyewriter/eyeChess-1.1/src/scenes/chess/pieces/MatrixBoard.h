#pragma once
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Pawn.h"

class MatrixBoard
{
protected:
    ChessPiece* board[8][8];

public:
    MatrixBoard();
    ChessPiece* get(int f, int r);
    void update(int f, int r, ChessPiece* cp);
};
