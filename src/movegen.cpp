#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GameState(WHITE);
    CHAI::MoveGen::initializePosition(GameState);
    CHAI::FEN::parse("2p5/1n1n4/8/8/8/8/KP6/8", GameState.piece, GameState.color);
    CHAI::FEN::displayBoard(GameState.piece, GameState.color);
    std::cout << std::endl;
    using namespace CHAI::MoveGen;
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