#include <iostream>
#include "defs.h"

// Main namespace of the CHAI chess engine
namespace CHAI
{
    class Board
    {
        // Definitions

    public:
    //For testing
        Board()
        {   
            Side = White;
            EnemySide = (Side == White) ? Black : White;
        };
        int MoveCount = 0;
        // Side the computer is playing
        int Side;
        // Enemy Side (calculated at initialization based on the Side)
        int EnemySide;
        // The board represetation with to arrays for color and piece data
        int Color[64] = {};
        int Piece[64] = {};
        // Data used for mailbox move generation
        int Mailbox[120] = {
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, 0, 1, 2, 3, 4, 5, 6, 7, -1,
            -1, 8, 9, 10, 11, 12, 13, 14, 15, -1,
            -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
            -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
            -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
            -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
            -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
            -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        // Corresponding array locations for the mailbox with the board squares
        int Mailbox64[64] = {
            21, 22, 23, 24, 25, 26, 27, 28,
            31, 32, 33, 34, 35, 36, 37, 38,
            41, 42, 43, 44, 45, 46, 47, 48,
            51, 52, 53, 54, 55, 56, 57, 58,
            61, 62, 63, 64, 65, 66, 67, 68,
            71, 72, 73, 74, 75, 76, 77, 78,
            81, 82, 83, 84, 85, 86, 87, 88,
            91, 92, 93, 94, 95, 96, 97, 98};
        // Offset data
        bool Slide[6] = {false, false, true, true, true, false};

        int Offset[6][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {-21, -19, -12, -8, 8, 12, 19, 21}, // Knight
            {-11, -9, 9, 11, 0, 0, 0, 0},       // Bishop
            {-10, -1, 1, 10, 0, 0, 0, 0},       // Rook
            {-11, -10, -9, -1, 1, 9, 10, 11},   // Queen
            {-11, -10, -9, -1, 1, 9, 10, 11}    // King
        };
        // Move generation using the mailbox method
        void MoveGen()
        {
            // Loop through all squares
            for (int Square = 0; Square < 64;)
            {
                // Check if its not the opponents piece
                if (Color[Square] == Side)
                {
                    GetMoves(Piece[Square], Square);
                };
                Square++;
            };
        };
        // Get all possible legal moves for a piece
        void GetMoves(int Piece, int Position)
        {
            // Target square of move
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
                                    std::cout << "Possible capture at Square " << Move << std::endl;
                                    MoveCount++;
                                }
                                // Move
                                else
                                {
                                    std::cout << "Possible move to Square " << Move << std::endl;
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
                    int Dir = (Side == White) ? -1 :1;
                    int DoubleFile = (Side == White) ? 6 : 1;
                    // Check validity of attack to the right
                    if (Mailbox[Mailbox64[Position] + 9 * Dir] != -1 && Color[Mailbox[Mailbox64[Position] + 9 * Dir]] == EnemySide)
                    {
                        std::cout << "Possible capture at Square " << Mailbox[Mailbox64[Position] + 9 * Dir] << " for " << Position << std::endl;
                        MoveCount++;
                    }
                    // Check validity of attack to the left
                    if (Mailbox[Mailbox64[Position] + 11 * Dir] != -1 && Color[Mailbox[Mailbox64[Position] + 11 * Dir]] == EnemySide)
                    {
                        std::cout << "Possible capture at Square " << Mailbox[Mailbox64[Position] + 11 * Dir] << " for " << Position << std::endl;
                        MoveCount++;
                    }
                    // Move forward
                    if (Mailbox[Mailbox64[Position] + 10 * Dir] != -1 && Color[Mailbox[Mailbox64[Position] + 10 * Dir]] == Empty)
                    {
                        std::cout << "Possible move to Square " << Mailbox[Mailbox64[Position] + 10] << " for " << Position << std::endl;
                        MoveCount++;
                    }
                    //Double Move
                    if (Row(Position) == DoubleFile && Color[Mailbox[Mailbox64[Position] + 20]] == Empty && Mailbox[Mailbox64[Position] + 20] != -1 && Color[Mailbox[Mailbox64[Position] + 10]] == Empty)
                    {
                        std::cout << "Possible move to Square " << Mailbox[Mailbox64[Position] + 20] << " for " << Position << std::endl;
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
                                    std::cout << "Possible capture at Square " << Move << " for " << Position << std::endl;
                                    MoveCount++;
                                    break;
                                }
                                // Move
                                else
                                {
                                    std::cout << "Possible move to Square " << Move << " for " << Position << std::endl;
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
