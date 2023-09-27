#include "fen.h"
#include "movegen.h"
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
    std::cout << "✔️[[ FEN 1 ] PASSED\n";
  } else {
    std::cout
        << "✖️[[ FEN 1 ] FAILED due to incorrect number of moves generated\n";
  }
  return 0;
}
