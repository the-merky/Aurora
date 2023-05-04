#include <iostream>
#include "defs.h"
#include "movegen-helpers.h"
#include "algebraic.h"
namespace CHAI
{
    namespace MoveGen
    {
        Position *GameState;
        // Functions
        void initializePosition(Position &Position)
        {
            GameState = &Position;
            Algebraic::setGlobalValues(Position);
        }
        //  Get all possible pseudo-legal moves for a piece
        void getMoves(int piece, int position, int side)
        {
            int enemySide = (side == WHITE) ? BLACK : WHITE;
            //  Target square of move
            int move;
            // Ray length
            int range = 1;
            // Check if the piece is a sliding piece
            if (!slide[piece - 1])
            { // It's a KNIGHT or a KING
                if (piece != PAWN)
                {
                    // Loop through all possible offsets
                    for (int i = 0; i < 8;)
                    {
                        move = mailbox[mailbox64[position] + offset[piece - 1][i]];
                        // If move is not out of bounds
                        if (move != -1)
                        {
                            // Not moving on a square which one's one piece occupies
                            if (GameState->color[move] != side)
                            {
                                // Capture
                                if (GameState->color[move] == enemySide)
                                {
                                    std::cout << Algebraic::convertToAlgebraic(position, move) << std::endl;
                                }
                                // move
                                else
                                {
                                    std::cout << Algebraic::convertToAlgebraic(position, move) << std::endl;
                                }
                            }
                        };
                        i++;
                    }
                }
                else if (piece == PAWN)
                {
                    // Direction the pawn is moving
                    int Dir = (side == WHITE) ? -1 : 1;
                    int DoubleFile = (side == WHITE) ? 6 : 1;
                    // Check validity of attack to the right
                    if (mailbox[mailbox64[position] + 9 * Dir] != -1 && GameState->color[mailbox[mailbox64[position] + 9 * Dir]] == enemySide)
                    {
                        std::cout << Algebraic::convertToAlgebraic(position, mailbox[mailbox64[position] + 9 * Dir]) << std::endl;
                    }
                    // Check validity of attack to the left
                    if (mailbox[mailbox64[position] + 11 * Dir] != -1 && GameState->color[mailbox[mailbox64[position] + 11 * Dir]] == enemySide)
                    {
                        std::cout << Algebraic::convertToAlgebraic(position, mailbox[mailbox64[position] + 11 * Dir]) << std::endl;
                    }
                    // move forward
                    if (mailbox[mailbox64[position] + 10 * Dir] != -1 && GameState->color[mailbox[mailbox64[position] + 10 * Dir]] == EMPTY)
                    {
                        std::cout << Algebraic::convertToAlgebraic(position, mailbox[mailbox64[position] + 10 * Dir]) << std::endl;
                    }
                    // Double move
                    if (row(position) == DoubleFile && GameState->color[mailbox[mailbox64[position] + 20 * Dir]] == EMPTY && mailbox[mailbox64[position] + 20 * Dir] != -1)
                    {
                        std::cout << Algebraic::convertToAlgebraic(position, mailbox[mailbox64[position] + 20 * Dir]) << std::endl;
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
                        move = mailbox[mailbox64[position] + offset[piece - 1][i] * range];
                        // Until a valid move
                        while (move != -1)
                        {
                            // Not moving on a square which one's one piece occupies
                            if (GameState->color[move] != side)
                            {
                                // Capture
                                if (enemySide == GameState->color[move])
                                {
                                    std::cout << Algebraic::convertToAlgebraic(position, move) << std::endl;

                                    break;
                                }
                                // move
                                else
                                {
                                    std::cout << Algebraic::convertToAlgebraic(position, move) << std::endl;
                                }
                            }
                            else
                            {
                                break;
                            }
                            // Ray length increases
                            range++;
                            // Recalculate move
                            move = mailbox[mailbox64[position] + offset[piece - 1][i] * range];
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
        void generate(int TargetSide)
        {
            std::cout << "MOVES FOUND:\n";
            // Loop through all squares
            for (int square = 0; square < 64;)
            {
                // Check if its not the opponents piece
                if (GameState->color[square] == TargetSide)
                {
                        getMoves(GameState->piece[square], square, TargetSide);
                };
                square++;
            };
        };

    };
};