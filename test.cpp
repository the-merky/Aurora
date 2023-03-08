#include "board.h"
#include "fen.h"
#include <iostream>
int main()
{

    using namespace CHAI;
    Board ChessBoard;
    // For testing:
    //  Pointers for Parsing
    int *pPiece = ChessBoard.Piece;
    int *pColor = ChessBoard.Color;
    FEN::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", pPiece, pColor);
    FEN::DisplayBoard(pPiece, pColor);
    std::cout <<  ChessBoard.EnemySide << std::endl;
    ChessBoard.MoveGen();
    std::cout << ChessBoard.MoveCount << " Possible Moves found\n";
    return 0;
};
