#include "board.h"
#include "fen.h"
#include <iostream>
int main()
{
    using namespace CHAI;
    Board ChessBoard;
    // Check if the code has reached here

    // For testing:
    //  Pointers for Parsing
    int *pPiece = ChessBoard.Piece;
    int *pColor = ChessBoard.Color;
    FEN::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", pPiece, pColor);
    FEN::DisplayBoard(pPiece, pColor);
    std::cout << ChessBoard.EnemySide << std::endl;
    ChessBoard.MoveGen(White);
    std::cout << ChessBoard.MoveCount << " Possible Moves found\n";
    std::cout << ChessBoard.ToAlgebricSquare(0);
    return 0;
};
