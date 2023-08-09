#include "eval.h"
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
  Node.Position.evalScore = Eval();
  // If reached desired depth
  if (currentDepth == depth) {
    return;
  }
  // Search for child nodes
  for (int i = 0; i < Node.Children.size();) {
    Node.Children.push_back(
        {makeMove(Node.Position.moves[i], Node.Position, WHITE)});
    search(depth, currentDepth + 1, Node.Children[Node.Children.size() - 1]);
  }
}

} // namespace MoveSearch
} // namespace Aurora
