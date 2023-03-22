#include <iostream>
#include <string>
#include "defs.h"
#include "fen.h"
#include "algebraic.h"

// Main namespace of the CHAI chess engine
namespace CHAI
{
    class Board
    {

    public:
        // For testing
        Board()
        {
        };
        // Bitboard of attakced squares
        U64 AttackedSquares[64] = {};

        // Functions

        // Move generation using the mailbox method
        void MoveGen(int TargetSide)
        {
            // Loop through all squares
            for (int Square = 0; Square < 64;)
            {
                // Check if its not the opponents piece
                if (Color[Square] == TargetSide)
                {
                    GetMoves(Piece[Square], Square, TargetSide);
                };
                Square++;
            };
        };
        // Change all occurences of Side to Whose
        //  Get all possible legal moves for a piece
        void GetMoves(int Piece, int Position, int Side)
        {
            // Side
            //  Target square of move
            int Move;
            // Ray length
            int Range = 1;
            // Check if the pice is a sliding piece
            if (!Slide[Piece - 1])
            { // It's a knight or a king
                if (Piece != Pawn)
                {
                    // Loop through all possible offsets
                    for (int i = 0; i < 8;)
                    {
                        Move = Mailbox[Mailbox64[Position] + Offset[Piece - 1][i]];
                        // If move is not out of bounds
                        if (Move != -1)
                        {
                            // Not moving on a square which one's one piece occupies
                            if (Color[Move] != Side)
                            {
                                // Capture
                                if (Color[Move] == EnemySide)
                                {
                                    std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Move) << std::endl;
                                    MoveCount++;
                                }
                                // Move
                                else
                                {
                                    std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Move) << std::endl;
                                    MoveCount++;
                                }
                            }
                        };
                        i++;
                    }
                }
                else if (Piece == Pawn)
                {
                    // Direction the pawn is moving
                    int Dir = (Side == White) ? -1 : 1;
                    int DoubleFile = (Side == White) ? 6 : 1;
                    // Check validity of attack to the right
                    if (Mailbox[Mailbox64[Position] + 9 * Dir] != -1 && Color[Mailbox[Mailbox64[Position] + 9 * Dir]] == EnemySide)
                    {
                        std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 9 * Dir]) << std::endl;
                        MoveCount++;
                    }
                    // Check validity of attack to the left
                    if (Mailbox[Mailbox64[Position] + 11 * Dir] != -1 && Color[Mailbox[Mailbox64[Position] + 11 * Dir]] == EnemySide)
                    {
                        std::cout << Algebraic::ConvertToAlgebraic(Piece , Position , Mailbox[Mailbox64[Position] + 11 * Dir]) << std::endl;
                        MoveCount++;
                    }
                    // Move forward
                    if (Mailbox[Mailbox64[Position] + 10 * Dir] != -1 && Color[Mailbox[Mailbox64[Position] + 10 * Dir]] == Empty)
                    {
                        std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 10 * Dir]) << std::endl;
                        MoveCount++;
                    }
                    // Double Move
                    if (Row(Position) == DoubleFile && Color[Mailbox[Mailbox64[Position] + 20 * Dir]] == Empty && Mailbox[Mailbox64[Position] + 20 * Dir] != -1)
                    {
                        std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 20 * Dir])<< std::endl;
                        MoveCount++;
                    }
                };
            }
            else if (Slide[Piece - 1])
            {
                // It's a sliding piece
                // Loop thorugh all offsets
                for (int i = 0; i < 8;)
                {
                    // Valid Offset
                    if (Offset[Piece - 1][i] != 0)
                    {
                        // Reset Range
                        Range = 1;
                        // Calculate the target square(for moving) by multplying the offset by the range and passing it into the mailbox array
                        Move = Mailbox[Mailbox64[Position] + Offset[Piece - 1][i] * Range];
                        // Until a valid move
                        while (Move != -1)
                        {
                            // Not moving on a square which one's one piece occupies
                            if (Color[Move] != Side)
                            {
                                // Capture
                                if (EnemySide == Color[Move])
                                {
                                    std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Move) << std::endl;
                                    MoveCount++;
                                    break;
                                }
                                // Move
                                else
                                {
                                    std::cout <<  Algebraic::ConvertToAlgebraic(Piece, Position, Move)<< std::endl;
                                    MoveCount++;
                                }
                            }
                            else
                            {
                                break;
                            }
                            // Ray length increases
                            Range++;
                            // Recalculate Move
                            Move = Mailbox[Mailbox64[Position] + Offset[Piece - 1][i] * Range];
                        }
                        i++;
                    }
                    else
                    {
                        break;
                    }
                };
            }
        };
    };
};
