#include "position.h"
#include <iostream>
#include "defs.h"
#include "movegen-helpers.h"
#include "algebraic.h"
namespace CHAI
{
    namespace MoveGen
    {
        int (*color)[64];
        int (*piece)[64];
        //std::vector<move> MoveList;
        bool bQCastlingRights;
        bool bKCastlingRights;
        bool wQCastlingRights;
        bool wKCastlingRights;
        // Functions
        void UpdatePosition(CHAI::Position Position)
        {
            color = &Position.color;
            piece = &Position.piece;
            bQCastlingRights = Position.bQCastlingRights;
            bKCastlingRights = Position.bKCastlingRights;
            wQCastlingRights = Position.wQCastlingRights;
            wKCastlingRights = Position.wKCastlingRights;
        }

        //  Get all possible pseudo-legal moves for a piece
        void GetMoves(int piece, int location, int side)
        {
            int enemySide = (side == white) ? black : white;
            //  Target square of move
            int move;
            // Ray length
            int range = 1;
            // Check if the pice is a sliding piece
            if (!slide[piece - 1])
            { // It's a knight or a king
                if (piece != pawn)
                {
                    // Loop through all possible offsets
                    for (int i = 0; i < 8;)
                    {
                        move = mailbox[mailbox64[location] + offset[piece - 1][i]];
                        // If move is not out of bounds
                        if (move != -1)
                        {
                            // Not moving on a square which one's one piece occupies
                            if ((*color)[move] != side)
                            {
                                // Capture
                                if ((*color)[move] == enemySide)
                                {
                                    std::cout << Algebraic::convertToAlgebraic(piece, location, move) << std::endl;
                                }
                                // move
                                else
                                {
                                    std::cout << Algebraic::convertToAlgebraic(piece, location, move) << std::endl;
                                }
                            }
                        };
                        i++;
                    }
                }
                else if (piece == pawn)
                {
                    // Direction the pawn is moving
                    int Dir = (side == white) ? -1 : 1;
                    int DoubleFile = (side == white) ? 6 : 1;
                    // Check validity of attack to the right
                    if (mailbox[mailbox64[location] + 9 * Dir] != -1 && (*color)[mailbox[mailbox64[location] + 9 * Dir]] == enemySide)
                    {
                        std::cout << Algebraic::convertToAlgebraic(piece, location, mailbox[mailbox64[location] + 9 * Dir]) << std::endl;
                    }
                    // Check validity of attack to the left
                    if (mailbox[mailbox64[location] + 11 * Dir] != -1 && (*color)[mailbox[mailbox64[location] + 11 * Dir]] == enemySide)
                    {
                        std::cout << Algebraic::convertToAlgebraic(piece, location, mailbox[mailbox64[location] + 11 * Dir]) << std::endl;
                    }
                    // move forward
                    if (mailbox[mailbox64[location] + 10 * Dir] != -1 && color[mailbox[mailbox64[location] + 10 * Dir]] == empty)
                    {
                        std::cout << Algebraic::convertToAlgebraic(piece, location, mailbox[mailbox64[location] + 10 * Dir]) << std::endl;
                    }
                    // Double move
                    if (row(location) == DoubleFile && color[mailbox[mailbox64[location] + 20 * Dir]] == empty && mailbox[mailbox64[location] + 20 * Dir] != -1)
                    {
                        std::cout << Algebraic::convertToAlgebraic(piece, location, mailbox[mailbox64[location] + 20 * Dir]) << std::endl;
                    }
                };
            }
            else if (slide[piece - 1])
            {
                // It's a sliding piece
                // Loop thorugh all offsets
                for (int i = 0; i < 8;)
                {
                    // Valid Offset
                    if (offset[piece - 1][i] != 0)
                    {
                        // Reset range
                        range = 1;
                        // Calculate the target square(for moving) by multplying the offset by the range and passing it into the mailbox array
                        move = mailbox[mailbox64[location] + offset[piece - 1][i] * range];
                        // Until a valid move
                        while (move != -1)
                        {
                            // Not moving on a square which one's one piece occupies
                            if ((*color)[move] != side)
                            {
                                // Capture
                                if (enemySide == (*color[move]))
                                {
                                    std::cout << Algebraic::convertToAlgebraic(piece, location, move) << std::endl;

                                    break;
                                }
                                // move
                                else
                                {
                                    std::cout << Algebraic::convertToAlgebraic(piece, location, move) << std::endl;
                                }
                            }
                            else
                            {
                                break;
                            }
                            // Ray length increases
                            range++;
                            // Recalculate move
                            move = mailbox[mailbox64[location] + offset[piece - 1][i] * range];
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
            //Set values from location parameter
            UpdatePosition(Position);

            // Loop through all squares
            for (int square = 0; square < 64;)
            {
                // Check if its not the opponents piece
                if ((*color)[square] == TargetSide)
                {
                    std::cout << "piece: " << piece[square] << " Square: " << square << std::endl;
                    GetMoves((*piece)[square], square, TargetSide);
                };
                square++;
            };
        };

    };
};