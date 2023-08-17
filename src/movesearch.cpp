#include "fen.h"
#include "movegen.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
namespace Aurora {
namespace MoveSearch {

inline Position makeMove(Move Move, Position Position) {
  class Position TempPos;
  TempPos.copyPosition(&Position);
  TempPos.piece[Move.targetSquare] = Position.piece[Move.startSquare];
  TempPos.piece[Move.startSquare] = EMPTY;
  return TempPos;
}
void search(int depth, int currentDepth, Node Node) {
  if (currentDepth > depth) {
    return;
  }
  std::cout << "currentDepth = " << currentDepth << std::endl;
  MoveGen::initializePosition(Node.position);
  MoveGen::updateAttackedSquares(BLACK);
  MoveGen::generate(WHITE);
  for (int i = 0; i < Node.position.moves.size();) {
    Node.children.push_back(
        {.position = makeMove(Node.position.moves[i], Node.position)});
    std::cout << "A\n";
    search(depth, currentDepth + 1, Node.children[Node.children.size() - 1]);
    std::cout << "B\n";
  }
}
} // namespace MoveSearch
} // namespace Aurora
// Test MoveSearch
int main() {
  using namespace Aurora;
  Node TestNode;
  FEN::parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR",
             TestNode.position.piece, TestNode.position.color);
  MoveSearch::search(24, 1, TestNode);
}
