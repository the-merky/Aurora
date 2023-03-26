#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GamePos;
    CHAI::FEN::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", GamePos.piece, GamePos.color);
    CHAI::FEN::displayBoard(GamePos.piece, GamePos.color);
    CHAI::MoveGen::UpdatePosition(GamePos);
    //Print the contents of the Movegen::Piece and MOvegen::Color arrays
    for (int i = 0; i<64; i++){
        std::cout << "Piece[" << i << "] = " << CHAI::MoveGen::piece[i] << std::endl;
        std::cout << "Color[" << i << "] = " << CHAI::MoveGen::color[i] << std::endl;
    }
    CHAI::MoveGen::Generate(white, GamePos);
    return 0;
}