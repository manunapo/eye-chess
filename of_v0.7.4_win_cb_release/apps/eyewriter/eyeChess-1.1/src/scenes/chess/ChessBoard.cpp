#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
    bool white = true;
    bool black = false;
    board[0][0] = new Rook(0, 0 ,white);
    board[0][1] = new Knight(0, 1, white);
    board[0][2] = new Bishop(0, 2, white);
    board[0][3] = new Queen(0, 3, white);
    board[0][4] = new King(0, 4, white);
    board[0][5] = new Bishop(0, 5, white);
    board[0][6] = new Knight(0, 6, white);
    board[0][7] = new Rook(0, 7, white);
    for(int i = 0; i < 8; i++)
    {
        board[1][i] = new Pawn( 1, i, white);
    }
    board[7][0] = new Rook(7,0, black);
    board[7][1] = new Knight(7,1, black);
    board[7][2] = new Bishop(7,2, black);
    board[7][3] = new Queen(7,3, black);
    board[7][4] = new King(7,4, black);
    board[7][5] = new Bishop(7,5, black);
    board[7][6] = new Knight(7,6, black);
    board[7][7] = new Rook(7,7, black);
    for(int i = 0; i < 8; i++)
    {
        board[6][i] = new Pawn(6,i, black);
    }
    for(int i = 2; i < 6; i++ )
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = 0;
        }
    }
}

bool ChessBoard::isFree(int f, int r)
{
    return board[f][r] == 0;
}

void ChessBoard::movePiece(int f, int r, int newF, int newR)
{
    board[newF][newR] = board[f][r];
    if(board[newF][newR] != 0)
        board[newF][newR]->updateBox(newF, newR);
}

string ChessBoard::getImage(int f, int r)
{
    return board[f][r]->getImage();
}
