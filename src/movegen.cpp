#include "movegen.h"
#include "fen.h"
int main()
{
    Aurora::Position GameState(WHITE);
    Aurora::MoveGen::initializePosition(GameState);
    Aurora::FEN::parse("2p5/1n1n4/8/p1p1p3/8/8/KP6/8", GameState.piece, GameState.color);
    Aurora::FEN::displayBoard(GameState.piece, GameState.color);
    std::cout << std::endl;
    using namespace Aurora::MoveGen;
    generate(WHITE);
    updateAttackedSquares(BLACK);
    for (int i = 0; i < 64; i++)
    {
        char output = (attackedSquares.test(i)) ? '0' : '+';
        if (i % 8 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << output << " ";
    };
    std::cout << std::endl;

    for (int i = 0; i < 64; i++)
    {
        char output = (defendedPieces.test(i)) ? '0' : '+';
        if (i % 8 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << output << " ";
    };
    std::cout << std::endl;
    return 0;
}