#pragma once
#include "pieces/ChessPiece.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Queen.h"
#include "pieces/King.h"
#include "pieces/Bishop.h"
#include "pieces/Pawn.h"
#include <string>

using namespace std;
class ChessBoard
{
protected:
    ChessPiece* board[8][8];
public:
    ChessBoard();
    bool isFree(int f, int r);
    void movePiece(int f, int r, int newF, int newR);
    string getImage(int f, int r);
};
