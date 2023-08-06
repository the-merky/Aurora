#include "node.h"
#include <stdio.h>
namespace Aurora {
namespace MoveSearch {

inline Position makeMove(Move Move, Position Position, int side) {
  class Position TempPos(side, true, &Position);
  TempPos.piece[Move.targetSquare] = Position.piece[Move.startSquare];
  TempPos.piece[Move.startSquare] = EMPTY;
  return TempPos;
}

} // namespace MoveSearch
} // namespace Aurora
