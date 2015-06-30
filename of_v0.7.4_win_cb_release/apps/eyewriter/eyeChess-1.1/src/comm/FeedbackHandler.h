#pragma once

class ChessBoard;

class FeedbackHandler
{
private:
    ChessBoard* chessBoard;

public:
    FeedbackHandler();
    FeedbackHandler(ChessBoard* cb);
    void informMove(int fromFile, int fromRow, int toFile, int toRow);
};

