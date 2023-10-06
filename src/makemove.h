#include "movegen.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdio.h>
namespace Aurora{
inline void makeMove(Move Move, Position Position, class Position &ReturnPos) {
  ReturnPos.copyPosition(Position);
  if (Move.startSquare == -3 || Move.startSquare == -4) {
    if (Position.side == WHITE) {
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
    // Update catling rights is KING or ROOK move
    if (ReturnPos.piece[Move.targetSquare] == KING) {
      if (ReturnPos.side == WHITE) {
        ReturnPos.wKCastlingRights = false;
        ReturnPos.wQCastlingRights = false;
      } else {
        ReturnPos.bKCastlingRights = false;
        ReturnPos.bQCastlingRights = false;
      }
    }
    if (ReturnPos.piece[Move.targetSquare] == ROOK) {
      if (ReturnPos.side == WHITE) {
        ReturnPos.wKCastlingRights = false;
        ReturnPos.wQCastlingRights = false;
      } else {
        ReturnPos.wKCastlingRights = false;
        ReturnPos.wQCastlingRights = false;
      }
    }
    // Update enpassant bitboard if pawn does a double move
    if(ReturnPos.piece[Move.targetSquare] == PAWN && ((Move.targetSquare - 16 == Move.startSquare) || (Move.targetSquare +16 == Move.startSquare))){
      if(ReturnPos.piece[Move.targetSquare] == BLACK){
        ReturnPos.bEnpassantPieces.set(Move.targetSquare);
      } else{
        ReturnPos.wEnpassantPieces.set(Move.targetSquare);
      } 
    }
  }  
}
}
