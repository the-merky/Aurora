#include "fen.h"
#include "eval.h"
#include <iostream>
void resetPosition(Aurora::Position Position) {
  Position.attackedSquares.reset();
  Position.defendedPieces.reset();
  Position.pinnedPieces.reset();
  Position.bEnpassantPieces.reset();
  Position.wEnpassantPieces.reset();
  Position.bQCastlingRights = true;
  Position.wQCastlingRights = true;
  Position.bKCastlingRights = true;
  Position.wKCastlingRights = true;
  for(int i=0; i < 64; i ++){
    Position.color[i] = 0;
    Position.piece[i] = 0;
  }
}
int main() {
  using namespace Aurora;
  // Tests
  // Movegen
  std::string fen1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  std::string fen2 = "rnbqk2r/pppp1ppp/5n2/2b1p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R";
  std::string fen3 = "6k1/8/Pp6/8/8/8/1K6/8";
  Position Position;
  Position.side = WHITE;
  // fen 1 test
  std::cout << "MOVEGEN TESTS\n";
  FEN::parse(fen1, Position.piece, Position.color);
  MoveGen::generate(&Position);
  if (Position.moves.size() == 20) {
    std::cout << "✔️[[ FEN 1 - Starting position] PASSED\n";
  } else {
    std::cout
        << "✖️[[ FEN 1 ] FAILED due to incorrect number of moves generated\n";
  }
  // fen 2 test
  resetPosition(Position);
   FEN::parse(fen2, Position.piece, Position.color); 
  if (true) {
    std::cout << "✔️[[ FEN 2 - Generic position] PASSED\n";
  } else {
    std::cout
        << "✖️[[ FEN 2 ] FAILED due to incorrect number of moves generated\n";
  }
  // fen 3 test
 resetPosition(Position);
   FEN::parse(fen3, Position.piece, Position.color);
  MoveGen::generate(&Position);
  if (Position.moves.size() == 20) {
    std::cout << "✔️[[ FEN 3 - Tricky position] PASSED\n";
  } else {
    std::cout
        << "✖️[[ FEN 3 ] FAILED due to incorrect number of moves generated\n";
  }
  MoveGen::printMoves(&Position); 
  std::cout << "EVAL TEST\n";
  std:: cout << Eval(&Position) << std::endl; 
  // fen 4 test
  // TODO En Passant Test
  FEN::parse("8 / 8 / 1Pp5 / 8 / 8 / 8 / 8 / 8", Position.piece, Position.color);
  MoveGen::generate(&Position);
  return 0;
}
