#include "movegen.h"
#include <stdio.h>
namespace Aurora {
namespace MoveSearch {
inline void search(int depth, Position *RootPosition) {
  for (int i = 0; i < RootPosition->moves.size();) {
    MoveGen::makeMove(RootPosition->moves[i], *RootPosition, WHITE);
  }
}
} // namespace MoveSearch
} // namespace Aurora
