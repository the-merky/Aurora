#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GameState(WHITE);
    CHAI::MoveGen::initializePosition(GameState);
    CHAI::FEN::parse("7b/8/8/8/8/2N5/8/K7", GameState.piece, GameState.color);
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
        char output = (pinnedPieces.test(i)) ? '0' : '+';
        if (i % 8 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << output << " ";
    };
    std::cout << std::endl;
    return 0;
}