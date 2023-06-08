#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GameState(WHITE);
    CHAI::MoveGen::initializePosition(GameState);
    CHAI::FEN::parse("8/8/8/8/1p1p4/2b5/1N1p4/K7", GameState.piece, GameState.color);
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
    return 0;
}