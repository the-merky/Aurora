#include "fen.h"
#include "movegen.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
namespace Aurora {
namespace MoveSearch {

inline void makeMove(Move Move, Position Position, class Position &ReturnPos) {
  ReturnPos.copyPosition(Position);
  // Make move on piece array
  ReturnPos.piece[Move.targetSquare] = Position.piece[Move.startSquare];
  ReturnPos.piece[Move.startSquare] = EMPTY;
  // And on color array
  ReturnPos.color[Move.targetSquare] = Position.color[Move.startSquare];
  ReturnPos.color[Move.startSquare] = EMPTY;
}
void search(int depth, int currentDepth, Node Node) {
  if (currentDepth > depth) {
    return;
  }
  std::cout << "currentDepth = " << currentDepth << std::endl;
  MoveGen::initializePosition(Node.position);
  std::cout << "1\n";
  MoveGen::updateAttackedSquares(BLACK);
  std::cout << "2\n";
  MoveGen::generate(WHITE);
  std::cout << "3\n";
  for (int i = 0; i < Node.position.moves.size();) {
    Node.children.push_back({});
    makeMove(Node.position.moves[i], Node.position,
             Node.children[Node.children.size() - 1].position);
    std::cout << "A\n";
    search(depth, currentDepth + 1, Node.children[Node.children.size() - 1]);
    std::cout << "B\n";
    i++;
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
  MoveSearch::search(2, 1, TestNode);
}
