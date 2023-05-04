#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GameState(BLACK);
    CHAI::MoveGen::initializePosition(GameState);
    CHAI::FEN::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", GameState.piece, GameState.color);
    CHAI::FEN::displayBoard(GameState.piece, GameState.color);
    using namespace CHAI::MoveGen;
    //Print the contents of the Movegen::Piece and Movegen::Color arrays
    generate(WHITE);
    return 0;
}