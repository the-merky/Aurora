#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GameState(WHITE);
    CHAI::MoveGen::initializePosition(GameState);
    CHAI::FEN::parse("n7/8/8/8/8/8/8/8", GameState.piece, GameState.color);
    CHAI::FEN::displayBoard(GameState.piece, GameState.color);
    std::cout << std::endl;
    using namespace CHAI::MoveGen;
    generate(WHITE);
    updateAttackedSquares(BLACK);
    for (int i = 0;i < attackedSquares.size(); i++)
    {
        char output = (attackedSquares.test(i)) ? '#' : '.';
        std::cout << output << ' ';
        if (i % 8 == 0)
        {
            std::cout << std::endl;
        }
    };
    std::cout << std::endl;

    return 0;
}