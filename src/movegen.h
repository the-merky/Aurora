#include "algebraic.h"
#include "defs.h"
#include "movegen-helpers.h"
#include <bitset>
#include <iostream>
#include <ostream>
namespace Aurora {
namespace MoveGen {
// Helper variables:
// Bitboards
std::bitset<64> attackedSquares;
std::bitset<64> pinnedPieces;
std::bitset<64> defendedPieces;
// Pointer to Position object
Position *GameState;
// Functions
inline void initializePosition(Position &Position) {
  GameState = &Position;
  Algebraic::setGlobalValues(Position);
}
//  Get all possible pseudo-legal targetSquares for a piece
inline void getMoves(int piece, int startSquare, int side,
                     bool attackedSquaresGen) {
  int enemySide = (side == WHITE) ? BLACK : WHITE;
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
          if (GameState->color[targetSquare] != side) {
            if (piece == KNIGHT) {
              // Capture
              if (GameState->color[targetSquare] == enemySide &&
                  !attackedSquaresGen && !pinnedPieces.test(startSquare)) {
                GameState->moves.push_back({startSquare, targetSquare});
              } else if (GameState->color[targetSquare] == side &&
                         attackedSquaresGen) {
                defendedPieces.set(targetSquare);
              }
              // Move
              else {
                if (attackedSquaresGen) {
                  attackedSquares.set(targetSquare);
                } else {
                  if (!pinnedPieces.test(startSquare)) {
                    GameState->moves.push_back({startSquare, targetSquare});
                  }
                }
              }
            } else if (piece == KING) {
              // Capture
              if (GameState->color[targetSquare] == enemySide &&
                  !attackedSquaresGen && !defendedPieces.test(targetSquare)) {
                GameState->moves.push_back({startSquare, targetSquare});
              }
              // Move
              else {
                if (attackedSquaresGen) {
                  attackedSquares.set(targetSquare);
                } else if (!attackedSquares.test(targetSquare) &&
                           !attackedSquaresGen &&
                           GameState->color[targetSquare] == EMPTY) {
                  GameState->moves.push_back({startSquare, targetSquare});
                }
              }
              // Castling
              // Queenside castling rights
              if (GameState->bKCastlingRights) {
                // Direciton of the move
                int castleDirection = (side == WHITE) ? 1 : -1;
                if (!attackedSquares.test(startSquare) &&
                    GameState->piece[startSquare + castleDirection] == EMPTY &&
                    !attackedSquares.test(startSquare + castleDirection) &&
                    GameState->piece[startSquare + (castleDirection * 2)] ==
                        EMPTY &&
                    !attackedSquares.test(startSquare +
                                          (castleDirection * 2))) {
                  GameState->moves.push_back({-3, 0});
                }
              }
              // Kingside castling rights
              if (GameState->bQCastlingRights) {
                // Direction of the move
                int castleDirection = (side == WHITE) ? -1 : 1;

                if (!attackedSquares.test(startSquare) &&
                    GameState->piece[startSquare + castleDirection] == EMPTY &&
                    !attackedSquares.test(startSquare + castleDirection) &&
                    GameState->piece[startSquare + (castleDirection * 2)] ==
                        EMPTY &&
                    !attackedSquares.test(startSquare +
                                          (castleDirection * 2)) &&
                    !attackedSquares.test(startSquare +
                                          (castleDirection * 3))) {
                  GameState->moves.push_back({-4, 0});
                }
              }
            }
          }
          if (GameState->color[targetSquare] == side && attackedSquaresGen) {
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
        if (GameState->color[mailbox[mailbox64[startSquare] + 9 * dir]] ==
            enemySide) {
          if (attackedSquaresGen) {
            attackedSquares.set(targetSquare);
          } else if (!pinnedPieces.test(startSquare)) {
            GameState->moves.push_back(
                {startSquare, mailbox[mailbox64[startSquare] + 9 * dir]});
          }
        } else if (GameState
                           ->color[mailbox[mailbox64[startSquare] + 9 * dir]] ==
                       side &&
                   attackedSquaresGen) {
          defendedPieces.set(startSquare + 9 * dir);
        }
      }
      // Check validity of attack to the left
      if (mailbox[mailbox64[startSquare] + 11 * dir] != -1) {
        if (GameState->color[mailbox[mailbox64[startSquare] + 11 * dir]] ==
            enemySide) {
          if (attackedSquaresGen) {
            attackedSquares.set(targetSquare);
          } else if (!pinnedPieces.test(startSquare)) {
            GameState->moves.push_back(
                {startSquare, mailbox[mailbox64[startSquare] + 11 * dir]});
          }
        } else if (GameState->color[mailbox[mailbox64[startSquare] +
                                            11 * dir]] == side &&
                   attackedSquaresGen) {
          defendedPieces.set(startSquare + 11 * dir);
        }
      }
      if (!attackedSquaresGen) {
        // Move forward
        if (mailbox[mailbox64[startSquare] + 10 * dir] != -1 &&
            GameState->color[mailbox[mailbox64[startSquare] + 10 * dir]] ==
                EMPTY &&
            !pinnedPieces.test(startSquare)) {
          GameState->moves.push_back(
              {startSquare, mailbox[mailbox64[startSquare] + 10 * dir]});
        }
        // Double move
        if (row(startSquare) == doubleFile &&
            GameState->color[mailbox[mailbox64[startSquare] + 20 * dir]] ==
                EMPTY &&
            GameState->color[mailbox[mailbox64[startSquare] + 10 * dir]] ==
                EMPTY &&
            mailbox[mailbox64[startSquare] + 20 * dir] != -1 &&
            !pinnedPieces.test(startSquare)) {
          GameState->moves.push_back(
              {startSquare, mailbox[mailbox64[startSquare] + 20 * dir]});
        }
        // En Passant
        if (side == WHITE) {
          if (startSquare ==
              GameState->wEnpassantPieces.test(startSquare - 1)) {
            // En passant to right
            GameState->moves.push_back({-1, dir});
          } else if (GameState->wEnpassantPieces.test(startSquare + 1)) {
            // En passant to left
            GameState->moves.push_back({-2, dir});
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
          if (GameState->color[targetSquare] != side) {
            // Capture
            if (enemySide == GameState->color[targetSquare]) {
              if (attackedSquaresGen) {
                if (ghostPiece < 0) {
                  ghostPiece = targetSquare;
                } else {
                  if (!(GameState->color[targetSquare] == side) &&
                      GameState->piece[targetSquare] == KING) {
                    pinnedPieces.set(ghostPiece);
                  } else {
                    break;
                  }
                }
              } else if (!pinnedPieces.test(startSquare)) {
                GameState->moves.push_back({startSquare, targetSquare});
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
                GameState->moves.push_back({startSquare, targetSquare});
              }
            }
          } else if (GameState->color[targetSquare] == side) {
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
inline void printMoves() {
  for (int i = 0; i < GameState->moves.size(); i++) {
    std::cout << Algebraic::convertToAlgebraic(GameState->moves[i].startSquare,
                                               GameState->moves[i].targetSquare)
              << " , ";
  }
}
inline void generate(int side) {
  // Loop through all squares
  for (int square = 0; square < 64;) {
    // Check if its not the opponents piece
    if (GameState->color[square] == side) {
      getMoves(GameState->piece[square], square, side, false);
    };
    square++;
  };
};
inline void updateAttackedSquares(int side) {
  // Loop through all squares
  for (int square = 0; square < 64;) {
    // Check if its the opponents piece
    if (GameState->color[square] == side) {
      getMoves(GameState->piece[square], square, side, true);
    };
    square++;
  };
};
} // namespace MoveGen
} // namespace Aurora
