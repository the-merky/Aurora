#include "movesearch.h"
#include <iostream>
// Test MoveSearch
int main() {
  using namespace Aurora;
  Node TestNode;
  FEN::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR",
             TestNode.position.piece, TestNode.position.color);
  MoveSearch::search(5, 1, TestNode);
}
std::cout<< ::
