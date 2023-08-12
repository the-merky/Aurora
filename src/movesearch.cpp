#include "movegen.h"
#include <stdio.h>
namespace Aurora {
namespace MoveSearch {

inline Position makeMove(Move Move, Position Position, int side) {
  class Position TempPos(side, true, &Position);
  TempPos.piece[Move.targetSquare] = Position.piece[Move.startSquare];
  TempPos.piece[Move.startSquare] = EMPTY;
  return TempPos;
}
void search(int depth, int currentDepth, Node Node) {
  if (currentDepth > depth) {
    return;
  }
  for (int i = 0; i < Node.children.size();) {
    MoveGen::initializePosition(Node.position);
    MoveGen::updateAttackedSquares(BLACK);
    MoveGen::generate(WHITE);
    Node.children.push_back(
        {makeMove(Node.position.moves[i], Node.position, WHITE)});
    search(depth, currentDepth + 1, Node.children[Node.children.size() - 1]);
  }
}
} // namespace MoveSearch
} // namespace Aurora
