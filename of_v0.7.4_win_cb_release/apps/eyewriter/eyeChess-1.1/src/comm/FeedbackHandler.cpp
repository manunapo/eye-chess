#include "FeedbackHandler.h"

FeedbackHandler::FeedbackHandler()
{
}

FeedbackHandler::FeedbackHandler(ChessBoard* cb)
{
    chessBoard = cb;
}

void FeedbackHandler::informMove(int fromFile, int fromRow, int toFile, int toRow)
{
    chessBoard->moveFromTo( fromFile, fromRow, toFile, toRow);
}
