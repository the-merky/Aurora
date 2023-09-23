#include "fen.h"
#include "movesearch.h"
#include <iostream>
int main() {
  using namespace Aurora;
  // Tests
  // Movegen
  std::string fen1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  std::string fen2 = "rnbqk2r/pppp1ppp/5n2/2b1p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R";
  std::string fen3 = "6k1/8/Pp6/8/8/8/1K6/8";
  Position Position;
  //fen1
  FEN::parse(fen1, Position.piece, Position.color);
  
  return 0;
}
