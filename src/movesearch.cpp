#include "searchtree.h"
#include <stdio.h>
namespace Aurora {
namespace MoveSearch {
SearchTree *SearchTree;
inline Position makeMove(Move Move, Position Position, int side) {
  class Position TempPos(side, true, &Position);
  TempPos.piece[Move.targetSquare] = Position.piece[Move.startSquare];
  TempPos.piece[Move.startSquare] = EMPTY;
  return TempPos;
}
inline void search(int depth, Position *RootPosition) {
  *SearchTree = *new class SearchTree(RootPosition);
  for (int i = 0; i < RootPosition->moves.size();) {
    makeMove(RootPosition->moves[i], *RootPosition, WHITE);
  }
}
} // namespace MoveSearch
} // namespace Aurora
