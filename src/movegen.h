#include "position.h"
#include <iostream>
#include "defs.h"
#include "movegen-helpers.h"
#include "algebraic.h"
namespace CHAI
{
    namespace MoveGen
    {
        int (*Color)[64];
        int (*Piece)[64];
        //std::vector<Move> MoveList;
        bool BQCastlingRights;
        bool BKCastlingRights;
        bool WQCastlingRights;
        bool WKCastlingRights;
        // Functions
        void UpdatePosition(CHAI::Position Position)
        {
            Color = &Position.Color;
            Piece = &Position.Piece;
            bool BQCastlingRights = Position.BQCastlingRights;
            bool BKCastlingRights = Position.BKCastlingRights;
            bool WQCastlingRights = Position.WQCastlingRights;
            bool WKCastlingRights = Position.WKCastlingRights;
        }
        //  Get all possible legal moves for a piece
        void GetMoves(int Piece, int Position, int Side)
        {
            int EnemySide = (Side == White) ? Black : White;
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
                            if ((*Color)[Move] != Side)
                            {
                                // Capture
                                if ((*Color)[Move] == EnemySide)
                                {
                                    std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Move) << std::endl;
                                }
                                // Move
                                else
                                {
                                    std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Move) << std::endl;
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
                    if (Mailbox[Mailbox64[Position] + 9 * Dir] != -1 && (*Color)[Mailbox[Mailbox64[Position] + 9 * Dir]] == EnemySide)
                    {
                        std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 9 * Dir]) << std::endl;
                    }
                    // Check validity of attack to the left
                    if (Mailbox[Mailbox64[Position] + 11 * Dir] != -1 && (*Color)[Mailbox[Mailbox64[Position] + 11 * Dir]] == EnemySide)
                    {
                        std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 11 * Dir]) << std::endl;
                    }
                    // Move forward
                    if (Mailbox[Mailbox64[Position] + 10 * Dir] != -1 && Color[Mailbox[Mailbox64[Position] + 10 * Dir]] == Empty)
                    {
                        std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 10 * Dir]) << std::endl;
                    }
                    // Double Move
                    if (Row(Position) == DoubleFile && Color[Mailbox[Mailbox64[Position] + 20 * Dir]] == Empty && Mailbox[Mailbox64[Position] + 20 * Dir] != -1)
                    {
                        std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 20 * Dir]) << std::endl;
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
                            if ((*Color)[Move] != Side)
                            {
                                // Capture
                                if (EnemySide == (*Color[Move]))
                                {
                                    std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Move) << std::endl;

                                    break;
                                }
                                // Move
                                else
                                {
                                    std::cout << Algebraic::ConvertToAlgebraic(Piece, Position, Move) << std::endl;
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
            };
        };
        void Generate(int TargetSide, CHAI::Position Position)
        {
            //Set values from Position parameter
            UpdatePosition(Position);

            // Loop through all squares
            for (int Square = 0; Square < 64;)
            {
                // Check if its not the opponents piece
                if ((*Color)[Square] == TargetSide)
                {
                    std::cout << "Piece: " << Piece[Square] << " Square: " << Square << std::endl;
                    GetMoves((*Piece)[Square], Square, TargetSide);
                };
                Square++;
            };
        };
       
    };
};