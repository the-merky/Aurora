#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GameState(WHITE);
    CHAI::MoveGen::initializePosition(GameState);
    CHAI::FEN::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", GameState.piece, GameState.color);
    CHAI::FEN::displayBoard(GameState.piece, GameState.color);
    using namespace CHAI::MoveGen;
    generate(WHITE);
    return 0;
}