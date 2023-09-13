#include "movesearch.h"
#include <iostream>
int main() {
  using namespace Aurora;
  // Tests
  // Movegen

  // Movesearch
  std::cout << "Movesearch test:\n";
  Node TestNode;
  FEN::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR",
                     TestNode.position.piece, TestNode.position.color); 
  MoveSearch::search(3, 1, TestNode);
  if (TestNode.children.size() == 20) {
    std::cout << "Depth 1: ✔️ Passed\n";
  } else {
    std::cout << "Depth 1: ❌Failed - children size(" << TestNode.children.size()
              << "/20)";
  } 
  return 0;
}
