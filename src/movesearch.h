#include "fen.h"
#include "movegen.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
namespace Aurora {
namespace MoveSearch {

inline void makeMove(Move Move, Position Position, class Position &ReturnPos) {
  ReturnPos.copyPosition(Position);
  if (Move.startSquare == -3 || -4) {

    if (Position.enemySide == BLACK) {
      // WHITE castles
      ReturnPos.wKCastlingRights = false;
      ReturnPos.wQCastlingRights = false;
      if (Move.startSquare == -3) {
        ReturnPos.piece[60] = EMPTY;
        ReturnPos.piece[63] = EMPTY;
        ReturnPos.piece[62] = KING;
        ReturnPos.piece[61] = ROOK;
      } else {
        ReturnPos.piece[60] = EMPTY;
        ReturnPos.piece[56] = EMPTY;
        ReturnPos.piece[58] = KING;
        ReturnPos.piece[59] = ROOK;
      }
    } else {
      // BLACK castles
      if (Move.startSquare == -3) {
        // KING side
        ReturnPos.piece[4] = EMPTY;
        ReturnPos.piece[7] = EMPTY;
        ReturnPos.piece[6] = KING;
        ReturnPos.piece[5] = ROOK;

      } else {
        // QUEEN side
        ReturnPos.piece[4] = EMPTY;
        ReturnPos.piece[0] = EMPTY;
        ReturnPos.piece[2] = KING;
        ReturnPos.piece[3] = ROOK;
      }
    }
  } else {
    // Make move on piece array
    ReturnPos.piece[Move.targetSquare] = Position.piece[Move.startSquare];
    ReturnPos.piece[Move.startSquare] = EMPTY;
    // And on color array
    ReturnPos.color[Move.targetSquare] = Position.color[Move.startSquare];
    ReturnPos.color[Move.startSquare] = EMPTY;
    if (ReturnPos.piece[Move.targetSquare] == KING) {
      if (ReturnPos.enemySide == BLACK) {
        ReturnPos.wKCastlingRights = false;
        ReturnPos.wQCastlingRights = false;
      } else {
        ReturnPos.wKCastlingRights = false;
        ReturnPos.wQCastlingRights = false;
      }
    }
    if (ReturnPos.piece[Move.targetSquare] == ROOK) {
      if (ReturnPos.enemySide == BLACK) {
        ReturnPos.wKCastlingRights = false;
        ReturnPos.wQCastlingRights = false;
      } else {
        ReturnPos.wKCastlingRights = false;
        ReturnPos.wQCastlingRights = false;
      }
    }
  }
}
inline void search(int depth, int currentDepth, Node Node) {
  if (currentDepth > depth) {
    return;
  }
  int side = (Node.position.enemySide == WHITE) ? BLACK : WHITE;
  MoveGen::initializePosition(Node.position);
  MoveGen::updateAttackedSquares(Node.position.enemySide);
  MoveGen::generate(side);
  for (int i = 0; i < Node.position.moves.size();) {
    Node.children.push_back({});
    makeMove(Node.position.moves[i], Node.position,
             Node.children[Node.children.size() - 1].position);
    search(depth, currentDepth + 1, Node.children[Node.children.size() - 1]);
    i++;
  }
}
} // namespace MoveSearch
} // namespace Aurora
