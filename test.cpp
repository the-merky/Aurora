#include "board.h"
#include <iostream>
int main()
{
    using namespace CHAI;
    Board ChessBoard;
    // Check if the code has reached here

    // For testing:
    //  Pointers for Parsing
    
    FEN::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", ChessBoard.Piece, ChessBoard.Color);
    FEN::DisplayBoard(ChessBoard.Piece, ChessBoard.Color);
    //Generate moves for white
    ChessBoard.MoveGen(White);
    std::cout << ChessBoard.MoveCount << " Possible Moves found\n";
    std::cout << ChessBoard.ToAlgebricSquare(0) << std:: endl;
    return 0;
};
