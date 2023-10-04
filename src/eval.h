#include"movegen.h"
#include <ostream>
namespace Aurora {
inline int getVal(int piece) {
  switch (piece) {
  case PAWN:
    return PAWNVAL;
  case KNIGHT:
    return KNIGHTVAL;
  case BISHOP:
    return BISHOPVAL;
  case ROOK:
    return ROOKVAL;
  case QUEEN:
    return QUEENVAL;
  default:
    return 0;
  }
}
inline int Eval(Position *Position) {
  int evalScore = 0;
  int wMaterial = 0;
  int bMaterial = 0;
  for (int i = 0; i < 64; i++) {
    if (Position->color[i] == WHITE && Position->piece[i] != KING){
      wMaterial = wMaterial + getVal(Position->piece[i]); 
    }
    else if (Position->color[i] == BLACK && Position->piece[i] != KING) {
      bMaterial += getVal(Position->piece[i]);
    }
  }
  evalScore = wMaterial - bMaterial;
  return evalScore;
};
} // namespace Aurora
