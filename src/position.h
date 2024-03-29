#include "defs.h"
#include "move.h"
#include <bitset>
#include <cstddef>
#include <vector>
namespace Aurora {
class Position {
public:
  std::vector<Move> moves;
  std::bitset<64> wEnpassantPieces;
  std::bitset<64> bEnpassantPieces;
  std::bitset<64> attackedSquares;
  std::bitset<64> pinnedPieces;
  std::bitset<64> defendedPieces;
  int color[64] = {};
  int piece[64] = {};
  int side;
  int evalScore;
  bool bQCastlingRights;
  bool bKCastlingRights;
  bool wQCastlingRights;
  bool wKCastlingRights;
  void copyPosition(Position &Position) {
    // Copy bool property and side
    side = (Position.side = WHITE) ? BLACK : WHITE;
    bQCastlingRights = Position.bQCastlingRights;
    bKCastlingRights = Position.bKCastlingRights;
    wQCastlingRights = Position.wQCastlingRights;
    // Copy color and piece arrays with loop
    for (int i = 0; i < 64; i++) {
      color[i] = Position.color[i];
      piece[i] = Position.piece[i];
    }
    // Copy en passant bitboards
    if (side == WHITE) {
      for (int i = 0; i < wEnpassantPieces.size(); i++) {
        if (Position.wEnpassantPieces.test(i)) {
          wEnpassantPieces.set(i);
        }
      }
    } else if (side == BLACK) {
      for (int i = 0; i < bEnpassantPieces.size(); i++) {
        if (Position.bEnpassantPieces.test(i)) {
          bEnpassantPieces.set(i);
        }
      }
    }
  }
};
}; // namespace Aurora
