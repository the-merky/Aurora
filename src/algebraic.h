#include "defs.h"
#include "node.h"
#include <string>
namespace Aurora {
namespace Algebraic {
// Namespace for algebraic notation to Aurora-Int parsing

// Convert a sqaure to algebraic notation
inline std::string toAlgebraicSquare(int square) {
  std::string output;
  switch (file(square)) {
  case 0:
    output += "a";
    break;
  case 1:
    output += "b";
    break;
  case 2:
    output += "c";
    break;
  case 3:
    output += "d";
    break;
  case 4:
    output += "e";
    break;
  case 5:
    output += "f";
    break;
  case 6:
    output += "g";
    break;
  case 7:
    output += "h";
    break;
  default:
    output += " ";
    break;
  };
  output += std::to_string(row(square) + 1);
  return output;
}
// Convert a move to algebraic notation
inline char pieceToChar(int piece, int color) {
  char pieceChar;
  switch (piece) {
  case PAWN:
    pieceChar = 'P';
    break;
  case KNIGHT:
    pieceChar = 'N';
    break;
  case BISHOP:
    pieceChar = 'B';
    break;
  case ROOK:
    pieceChar = 'R';
    break;
  case QUEEN:
    pieceChar = 'Q';
    break;
  case KING:
    pieceChar = 'K';
    break;
  default:
    pieceChar = ' ';
    break;
  };
  if (color == WHITE) {
    pieceChar = toupper(pieceChar);
  } else if (color == BLACK) {
    pieceChar = tolower(pieceChar);
  }
  return pieceChar;
}
inline std::string convertToAlgebraic(Position *Position, Move Move) {
  // Starting square (with) piece
  std::string algebricMove = "";
  if (Position->piece[Move.startSquare] == PAWN) {
    algebricMove += toAlgebraicSquare(Move.startSquare);
  } else {
    algebricMove +=
        pieceToChar(Position->piece[Move.startSquare], Position->color[Move.startSquare]);
    algebricMove += toAlgebraicSquare(Move.startSquare);
  };
  // Move with capture
  if (Position->color[Move.targetSquare] == !Position->side || EMPTY) {
    algebricMove += "x";
    algebricMove += toAlgebraicSquare(Move.targetSquare);
  }
  // Move without capture
  else if (Position->color[Move.targetSquare] == EMPTY) {
    algebricMove += "-";
    algebricMove += toAlgebraicSquare(Move.targetSquare);
  };
  return algebricMove;
};
} // namespace Algebraic
} // namespace Aurora
