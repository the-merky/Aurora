#include "movegen.h"
#include "fen.h"
int main()
{
    Aurora::Position GameState(WHITE);
    Aurora::MoveGen::initializePosition(GameState);
    Aurora::FEN::parse("8/8/8/8/2n5/8/1p6/1K6", GameState.piece, GameState.color);
    Aurora::FEN::displayBoard(GameState.piece, GameState.color);
    std::cout << std::endl;
    using namespace Aurora::MoveGen;
    updateAttackedSquares(BLACK);
    generate(WHITE);
    
    std::cout << "ATTACKED SQUARES:" << std::endl;
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
    std::cout << "PINNED PIECES:" << std::endl;

    for (int i = 0; i < 64; i++)
    {
        char output = (pinnedPieces.test(i)) ? '0' : '+';
        if (i % 8 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << output << " ";
    };
    std::cout << std::endl;
    std::cout << "DEFENDED PIECES:" << std::endl;
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