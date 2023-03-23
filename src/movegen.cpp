#include "movegen.h"
#include "fen.h"
int main()
{
    CHAI::Position GamePos;
    CHAI::FEN::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", GamePos.Piece, GamePos.Color);
    CHAI::FEN::DisplayBoard(GamePos.Piece, GamePos.Color);
    CHAI::MoveGen::UpdatePosition(GamePos);
    //Print the contents of the Movegen::Piece and MOvegen::Color arrays
    for (int i = 0; i<64; i++){
        std::cout << "Piece[" << i << "] = " << CHAI::MoveGen::Piece[i] << std::endl;
        std::cout << "Color[" << i << "] = " << CHAI::MoveGen::Color[i] << std::endl;
    }
    CHAI::MoveGen::Generate(White, GamePos);
    return 0;
}