#include "algebraic.h"
#include "defs.h"
#include "movegen-helpers.h"
#include <bitset>
#include <iostream>
#include <ostream>
namespace Aurora {
namespace MoveGen {
// Bitboards
std::bitset<64> attackedSquares;
std::bitset<64> pinnedPieces;
std::bitset<64> defendedPieces;
//  Get all possible pseudo-legal moves for a piece
inline void getMovesForPiece(Position *Position, int startSquare,
                             bool attackedSquaresGen) {
  int side = Position->side;
  int enemySide = (Position->side == WHITE) ? BLACK : WHITE;
  int piece = Position->piece[startSquare];
  //  Target square of move
  int targetSquare;
  // Ray length
  int range = 1;
  // Check if the piece is a sliding piece
  if (!slide[piece - 1]) {
    // It's a KNIGHT or a KING
    if (piece != PAWN) {
      // Loop through all possible offsets
      for (int i = 0; i < 8;) {
        targetSquare = mailbox[mailbox64[startSquare] + offset[piece - 1][i]];
        // If targetSquare is not out of bounds
        if (targetSquare != -1) {
          // Not moving on a square which one's one piece occupies
          if (Position->color[targetSquare] != side) {
            if (piece == KNIGHT) {
              // Capture
              if (Position->color[targetSquare] == enemySide &&
                  !attackedSquaresGen && !pinnedPieces.test(startSquare)) {
                Position->moves.push_back({startSquare, targetSquare});
              } else if (Position->color[targetSquare] == side &&
                         attackedSquaresGen) {
                defendedPieces.set(targetSquare);
              }
              // Move
              else {
                if (attackedSquaresGen) {
                  attackedSquares.set(targetSquare);
                } else {
                  if (!pinnedPieces.test(startSquare)) {
                    Position->moves.push_back({startSquare, targetSquare});
                  }
                }
              }
            } else if (piece == KING) {
              // Capture
              if (Position->color[targetSquare] == enemySide &&
                  !attackedSquaresGen && !defendedPieces.test(targetSquare)) {
                Position->moves.push_back({startSquare, targetSquare});
              }
              // Move
              else {
                if (attackedSquaresGen) {
                  attackedSquares.set(targetSquare);
                } else if (!attackedSquares.test(targetSquare) &&
                           !attackedSquaresGen &&
                           Position->color[targetSquare] == EMPTY) {
                  Position->moves.push_back({startSquare, targetSquare});
                }
              }
              // Castling
              // Queenside castling rights
              if (Position->bKCastlingRights) {
                // Direciton of the move
                int castleDirection = (side == WHITE) ? 1 : -1;
                if (!attackedSquares.test(startSquare) &&
                    Position->piece[startSquare + castleDirection] == EMPTY &&
                    !attackedSquares.test(startSquare + castleDirection) &&
                    Position->piece[startSquare + (castleDirection * 2)] ==
                        EMPTY &&
                    !attackedSquares.test(startSquare +
                                          (castleDirection * 2))) {
                  Position->moves.push_back({-3, 0});
                }
              }
              // Kingside castling rights
              if (Position->bQCastlingRights) {
                // Direction of the move
                int castleDirection = (side == WHITE) ? -1 : 1;

                if (!attackedSquares.test(startSquare) &&
                    Position->piece[startSquare + castleDirection] == EMPTY &&
                    !attackedSquares.test(startSquare + castleDirection) &&
                    Position->piece[startSquare + (castleDirection * 2)] ==
                        EMPTY &&
                    !attackedSquares.test(startSquare +
                                          (castleDirection * 2)) &&
                    !attackedSquares.test(startSquare +
                                          (castleDirection * 3))) {
                  Position->moves.push_back({-4, 0});
                }
              }
            }
          }
          if (Position->color[targetSquare] == side && attackedSquaresGen) {
            defendedPieces.set(targetSquare);
          }
        };
        i++;
      }
    } else if (piece == PAWN) {
      // Direction the pawn is moving
      int dir = (side == WHITE) ? -1 : 1;
      int doubleFile = (side == WHITE) ? 6 : 1;
      // Check validity of attack to the right
      if (mailbox[mailbox64[startSquare] + 9 * dir] != -1) {
        if (Position->color[mailbox[mailbox64[startSquare] + 9 * dir]] ==
            enemySide) {
          if (attackedSquaresGen) {
            attackedSquares.set(targetSquare);
          } else if (!pinnedPieces.test(startSquare)) {
            Position->moves.push_back(
                {startSquare, mailbox[mailbox64[startSquare] + 9 * dir]});
          }
        } else if (Position->color[mailbox[mailbox64[startSquare] + 9 * dir]] ==
                       side &&
                   attackedSquaresGen) {
          defendedPieces.set(startSquare + 9 * dir);
        }
      }
      // Check validity of attack to the left
      if (mailbox[mailbox64[startSquare] + 11 * dir] != -1) {
        if (Position->color[mailbox[mailbox64[startSquare] + 11 * dir]] ==
            enemySide) {
          if (attackedSquaresGen) {
            attackedSquares.set(targetSquare);
          } else if (!pinnedPieces.test(startSquare)) {
            Position->moves.push_back(
                {startSquare, mailbox[mailbox64[startSquare] + 11 * dir]});
          }
        } else if (Position->color[mailbox[mailbox64[startSquare] +
                                           11 * dir]] == side &&
                   attackedSquaresGen) {
          defendedPieces.set(startSquare + 11 * dir);
        }
      }
      if (!attackedSquaresGen) {
        // Move forward
        if (mailbox[mailbox64[startSquare] + 10 * dir] != -1 &&
            Position->color[mailbox[mailbox64[startSquare] + 10 * dir]] ==
                EMPTY &&
            !pinnedPieces.test(startSquare)) {
          Position->moves.push_back(
              {startSquare, mailbox[mailbox64[startSquare] + 10 * dir]});
        }
        // Double move
        if (row(startSquare) == doubleFile &&
            Position->color[mailbox[mailbox64[startSquare] + 20 * dir]] ==
                EMPTY &&
            Position->color[mailbox[mailbox64[startSquare] + 10 * dir]] ==
                EMPTY &&
            mailbox[mailbox64[startSquare] + 20 * dir] != -1 &&
            !pinnedPieces.test(startSquare)) {
          Position->moves.push_back(
              {startSquare, mailbox[mailbox64[startSquare] + 20 * dir]});
        }
        // En Passant
        if (side == WHITE) {
          if (startSquare == Position->wEnpassantPieces.test(startSquare - 1)) {
            // En passant to right
            Position->moves.push_back({-1, dir});
          } else if (Position->wEnpassantPieces.test(startSquare + 1)) {
            // En passant to left
            Position->moves.push_back({-2, dir});
          }
        }
      }
    }
  } else if (slide[piece - 1]) {
    // It's a sliding piece
    // Loop thorugh all offsets
    for (int i = 0; i < 8;) {
      // Valid Offset
      if (offset[piece - 1][i] != 0) {
        // Reset range
        range = 1;
        // Calculate the target square(for moving) by multplying the offset by
        // the range and passing it into the mailbox array
        targetSquare =
            mailbox[mailbox64[startSquare] + offset[piece - 1][i] * range];
        // Helper variable exclusively for the attackedSquaresGen. Helps to the
        // count of the piece the attack is "going through"
        int ghostPiece = -1;
        // Until a valid targetSquare
        while (targetSquare != -1) {

          // Not moving on a square which one's one piece occupies
          if (Position->color[targetSquare] != side) {
            // Capture
            if (enemySide == Position->color[targetSquare]) {
              if (attackedSquaresGen) {
                if (ghostPiece < 0) {
                  ghostPiece = targetSquare;
                } else {
                  if (!(Position->color[targetSquare] == side) &&
                      Position->piece[targetSquare] == KING) {
                    pinnedPieces.set(ghostPiece);
                  } else {
                    break;
                  }
                }
              } else if (!pinnedPieces.test(startSquare)) {
                Position->moves.push_back({startSquare, targetSquare});
                break;
              }
            }
            // Move
            else {

              if (attackedSquaresGen) {

                if (ghostPiece < 0) {
                  attackedSquares.set(targetSquare);
                }
              } else if (!pinnedPieces.test(startSquare)) {
                Position->moves.push_back({startSquare, targetSquare});
              }
            }
          } else if (Position->color[targetSquare] == side) {
            if (attackedSquaresGen) {
              defendedPieces.set(targetSquare);
            }
            break;
          }
          // Ray length increases
          range++;
          // Recalculate targetSquare
          targetSquare =
              mailbox[mailbox64[startSquare] + offset[piece - 1][i] * range];
        }
        i++;
      } else {
        break;
      }
    };
  }
}
inline void printMoves(Position *Position) {
  for (int i = 0; i < Position->moves.size(); i++) {
    std::cout << Algebraic::convertToAlgebraic(Position->moves[i].startSquare,
                                               Position->moves[i].targetSquare)
              << " , ";
  }
}
inline void getMoves(Position *Position) {
  // Loop through all squares
  for (int square = 0; square < 64;) {
    // Check if its not the opponents piece
    if (Position->color[square] == Position->side) {
      getMovesForPiece(Position, square, false);
    };
    square++;
  };
};
inline void updateAttackedSquares(Position *Position) {
  int enemySide = (Position->side == WHITE) ? BLACK : WHITE;
  // Loop through all squares
  for (int square = 0; square < 64;) {
    // Check if its the opponents piece
    if (Position->color[square] == enemySide) {
      getMovesForPiece(Position, square, true);
    };
    square++;
  };
};
} // namespace MoveGen
} // namespace Aurora
