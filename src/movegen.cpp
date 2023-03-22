#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GamePos;
    CHAI::FEN::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", GamePos.Piece, GamePos.Color);
    CHAI::FEN::DisplayBoard(GamePos.Piece, GamePos.Color);
    CHAI::MoveGen::Generate(Black, GamePos);
    return 0;
}