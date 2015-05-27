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

    firstSelectedF = -1;
    firstSelectedR = -1;
    secondSelectedF = -1;
    secondSelectedR = -1;
}

bool ChessBoard::isFree(int f, int r)
{
    return board[f][r] == 0;
}

string ChessBoard::getImage(int f, int r)
{
    return board[f][r]->getImage();
}

void ChessBoard::boxSelected(ButtonTrigger buttons[8][8], int f, int r)
{
    if(firstSelectedF != -1)
    {
        secondSelectedF = f;
        secondSelectedR = r;
        if(!board[firstSelectedF][firstSelectedR] == 0)
        {
            bool canMove = board[firstSelectedF][firstSelectedR]->canMove(getPlacesMatrix(), secondSelectedF, secondSelectedR);
            bool isOtherColor = board[firstSelectedF][firstSelectedR]->isWhite();
            bool isFree = board[secondSelectedF][secondSelectedR] == 0;
            if(!isFree)
            {
                isOtherColor = isOtherColor && !board[secondSelectedF][secondSelectedR]->isWhite();
                canMove = canMove && isOtherColor;
                cout << "Not free" << endl;
            }

            if(canMove)
            {
                board[secondSelectedF][secondSelectedR] = board[firstSelectedF][firstSelectedR];
                board[secondSelectedF][secondSelectedR]->updateBox(secondSelectedF, secondSelectedR);
                ButtonTrigger aux = buttons[secondSelectedF][secondSelectedR];
                buttons[secondSelectedF][secondSelectedR] = buttons[firstSelectedF][firstSelectedR];
                buttons[firstSelectedF][firstSelectedR] = aux;
                board[firstSelectedF][firstSelectedR] = 0;
                firstSelectedF = -1;
                firstSelectedR = -1;
                secondSelectedF = -1;
                secondSelectedR = -1;
            }
        }
        else
        {
            cout << "First box invalid" << endl;
        }
        firstSelectedF = -1;
        firstSelectedR = -1;
        secondSelectedF = -1;
        secondSelectedR = -1;

    }
    else
    {
        if(!isFree( f, r))
        {
            firstSelectedF = f;
            firstSelectedR = r;
        }
        else
        {
            cout << "Pick first again" << endl;
        }
    }
}

int** ChessBoard::getPlacesMatrix()
{
    int** places;
    places = new int*[8];
    for(int i = 0; i < 8; i++ )
    {
        places[i] = new int[8];
        for(int j = 0; j < 8; j++)
        {
            if(board[i][j] == 0)
            {
                places[i][j] = 0;
            }
            else
            {
                if(board[i][j]->isWhite())
                {
                    places[i][j] = 1;
                }
                else
                {
                    places[i][j] = 2;
                }
            }
        }
    }
    return places;
}
