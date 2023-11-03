#include "eval.h"
#include "fen.h"
#include <iostream>
int main() {
  using namespace Aurora;
  Position Position;
  FEN::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", Position.piece,
             Position.color);
  MoveGen::generate(&Position);
}
