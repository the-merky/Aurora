#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GamePos;
    CHAI::FEN::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", GamePos.piece, GamePos.color);
    CHAI::FEN::displayBoard(GamePos.piece, GamePos.color);
    using namespace CHAI::MoveGen;
    CHAI::MoveGen::UpdatePosition(GamePos);
    //Print the contents of the Movegen::Piece and MOvegen::Color arrays
    for (int i = 0; i< 64; i++){
        std::cout << "Piece[" << i << "] = " << (*piece)[i] << std::endl;
        std::cout << "Color[" << i << "] = " << (*color)[i] << std::endl;
    }
    Generate(white, GamePos);
    return 0;
}