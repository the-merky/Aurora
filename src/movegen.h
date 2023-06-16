#include <iostream>
#include <bitset>
#include "defs.h"
#include "movegen-helpers.h"
#include "algebraic.h"
namespace CHAI
{
    namespace MoveGen
    {
        // Helper variables
        std::bitset<64> attackedSquares;
        std::bitset<64> pinnedPieces;
        Position *GameState;
        // Functions
        void initializePosition(Position &Position)
        {
            GameState = &Position;
            Algebraic::setGlobalValues(Position);
        }
        // Checks if the move is legal
        bool isInCheck(int square)
        {
            if (attackedSquares.test(square))
            {
                return false;
            }
            return true;
        }
        //  Get all possible pseudo-legal targetSquares for a piece
        void getMoves(int piece, int startSquare, int side, bool attackedSquaresGen)
        {
            int enemySide = (side == WHITE) ? BLACK : WHITE;
            //  Target square of move
            int targetSquare;
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
                        targetSquare = mailbox[mailbox64[startSquare] + offset[piece - 1][i]];
                        // If targetSquare is not out of bounds
                        if (targetSquare != -1)
                        {
                            // Not moving on a square which one's one piece occupies
                            if (GameState->color[targetSquare] != side)
                            {
                                // Capture
                                if (GameState->color[targetSquare] == enemySide)
                                {
                                    if (attackedSquaresGen)
                                    {
                                        attackedSquares.set(targetSquare);
                                    }
                                    else
                                    {
                                        std::cout << Algebraic::convertToAlgebraic(startSquare, targetSquare) << std::endl;
                                        GameState->moves.push_back({startSquare, targetSquare});
                                    }
                                }
                                // Move
                                else
                                {
                                    if (attackedSquaresGen)
                                    {
                                        attackedSquares.set(targetSquare);
                                    }
                                    else
                                    {
                                        std::cout << Algebraic::convertToAlgebraic(startSquare, targetSquare) << std::endl;
                                        if (piece == KING)
                                        {
                                            if (isInCheck(targetSquare))
                                            {
                                                GameState->moves.push_back({startSquare, targetSquare});
                                            }
                                        }
                                        else
                                        {
                                            GameState->moves.push_back({startSquare, targetSquare});
                                        }
                                    }
                                }
                            }
                        };
                        i++;
                    }
                }
                else if (piece == PAWN)
                {
                    // Direction the pawn is moving
                    int dir = (side == WHITE) ? -1 : 1;
                    int doubleFile = (side == WHITE) ? 6 : 1;
                    // Check validity of attack to the right
                    if (mailbox[mailbox64[startSquare] + 9 * dir] != -1 && GameState->color[mailbox[mailbox64[startSquare] + 9 * dir]] == enemySide)
                    {
                        if (attackedSquaresGen)
                        {
                            attackedSquares.set(targetSquare);
                        }
                        else
                        {
                            std::cout << Algebraic::convertToAlgebraic(startSquare, mailbox[mailbox64[startSquare] + 9 * dir]) << std::endl;
                            GameState->moves.push_back({startSquare, mailbox[mailbox64[startSquare] + 9 * dir]});
                        }
                    }
                    // Check validity of attack to the left
                    if (mailbox[mailbox64[startSquare] + 11 * dir] != -1 && GameState->color[mailbox[mailbox64[startSquare] + 11 * dir]] == enemySide)
                    {
                        if (attackedSquaresGen)
                        {
                            attackedSquares.set(targetSquare);
                        }
                        else
                        {
                            std::cout << Algebraic::convertToAlgebraic(startSquare, mailbox[mailbox64[startSquare] + 11 * dir]) << std::endl;
                            GameState->moves.push_back({startSquare, mailbox[mailbox64[startSquare] + 11 * dir]});
                        }
                    }
                    // Move forward
                    if (mailbox[mailbox64[startSquare] + 10 * dir] != -1 && GameState->color[mailbox[mailbox64[startSquare] + 10 * dir]] == EMPTY)
                    {
                        std::cout << Algebraic::convertToAlgebraic(startSquare, mailbox[mailbox64[startSquare] + 10 * dir]) << std::endl;
                        GameState->moves.push_back({startSquare, mailbox[mailbox64[startSquare] + 10 * dir]});
                    }
                    // Double move
                    if (row(startSquare) == doubleFile && GameState->color[mailbox[mailbox64[startSquare] + 20 * dir]] == EMPTY && mailbox[mailbox64[startSquare] + 20 * dir] != -1)
                    {
                        std::cout << Algebraic::convertToAlgebraic(startSquare, mailbox[mailbox64[startSquare] + 20 * dir]) << std::endl;
                        GameState->moves.push_back({startSquare, mailbox[mailbox64[startSquare] + 20 * dir]});
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
                        targetSquare = mailbox[mailbox64[startSquare] + offset[piece - 1][i] * range];
                        // Helper variable exclusively for the attackedSquaresGen. Helps to the count of the piece the attack is "going through"
                        int ghostPiece = -1;
                        // Until a valid targetSquare
                        while (targetSquare != -1)
                        {

                            // Not moving on a square which one's one piece occupies
                            if (GameState->color[targetSquare] != side)
                            {
                                // Capture
                                if (enemySide == GameState->color[targetSquare])
                                {
                                    if (attackedSquaresGen)
                                    {
                                        if (ghostPiece < 0)
                                        {
                                            ghostPiece = targetSquare;
                                            std::cout << "Ghostpiece was set to " << targetSquare << " Its value is now " << ghostPiece << std::endl;
                                        }
                                        else
                                        {
                                            if (!(GameState->color[targetSquare] == side) && GameState->piece[targetSquare] == KING)
                                            {
                                                pinnedPieces.set(ghostPiece);
                                            }
                                            else
                                            {
                                                break;
                                            }
                                        }
                                    }
                                    else if (!pinnedPieces.test(startSquare))
                                    {
                                        std::cout << Algebraic::convertToAlgebraic(startSquare, targetSquare) << std::endl;
                                        GameState->moves.push_back({startSquare, targetSquare});
                                        break;
                                    }
                                }
                                // Move
                                else
                                {

                                    if (attackedSquaresGen)
                                    {
                                        if (ghostPiece < 0)
                                        {
                                            attackedSquares.set(targetSquare);
                                        }
                                    }
                                    else
                                    {
                                        std::cout << Algebraic::convertToAlgebraic(startSquare, targetSquare) << std::endl;
                                        GameState->moves.push_back({startSquare, targetSquare});
                                    }
                                }
                            }
                            else
                            {
                                break;
                            }
                            // Ray length increases
                            range++;
                            // Recalculate targetSquare
                            targetSquare = mailbox[mailbox64[startSquare] + offset[piece - 1][i] * range];
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
        void generate(int side)
        {
            std::cout << "MOVES FOUND:\n";
            // Loop through all squares
            for (int square = 0; square < 64;)
            {
                // Check if its not the opponents piece
                if (GameState->color[square] == side)
                {
                    getMoves(GameState->piece[square], square, side, false);
                };
                square++;
            };
        };
        void updateAttackedSquares(int side)
        {
            // Loop through all squares
            for (int square = 0; square < 64;)
            {
                // Check if its the opponents piece
                if (GameState->color[square] == side)
                {
                    getMoves(GameState->piece[square], square, side, true);
                };
                square++;
            };
        };
    };
};
