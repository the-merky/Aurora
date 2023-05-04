#include "board.h"
#include <iostream>
int main()
{
    using namespace CHAI;
    Board ChessBoard;

    // For testing:
    //Start position
    FEN::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", ChessBoard.Piece, ChessBoard.Color);
    FEN::DisplayBoard(ChessBoard.Piece, ChessBoard.Color);
    //Generate moves for WHITE
    ChessBoard.MoveGen(WHITE);
    //Display the moves
    std::cout << ChessBoard.MoveCount << " Possible Moves found\n";
    return 0;
};
