#include <iostream>
#include "defs.h"
#include "fen.h"
#include <string>

// Main namespace of the CHAI chess engine
namespace CHAI
{
    class Board
    {

    public:
        // For testing
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
                                    std::cout << ConvertToAlgebraic(Piece, Position, Move) << std::endl;
                                    MoveCount++;
                                }
                                // Move
                                else
                                {
                                    std::cout << ConvertToAlgebraic(Piece, Position, Move) << std::endl;
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
                        std::cout << ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 9 * Dir]) << std::endl;
                        MoveCount++;
                    }
                    // Check validity of attack to the left
                    if (Mailbox[Mailbox64[Position] + 11 * Dir] != -1 && Color[Mailbox[Mailbox64[Position] + 11 * Dir]] == EnemySide)
                    {
                        std::cout << ConvertToAlgebraic(Piece , Position , Mailbox[Mailbox64[Position] + 11 * Dir]) << std::endl;
                        MoveCount++;
                    }
                    // Move forward
                    if (Mailbox[Mailbox64[Position] + 10 * Dir] != -1 && Color[Mailbox[Mailbox64[Position] + 10 * Dir]] == Empty)
                    {
                        std::cout << ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 10 * Dir]) << std::endl;
                        MoveCount++;
                    }
                    // Double Move
                    if (Row(Position) == DoubleFile && Color[Mailbox[Mailbox64[Position] + 20 * Dir]] == Empty && Mailbox[Mailbox64[Position] + 20 * Dir] != -1)
                    {
                        std::cout << ConvertToAlgebraic(Piece, Position, Mailbox[Mailbox64[Position] + 20 * Dir])<< std::endl;
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
                                    std::cout << ConvertToAlgebraic(Piece, Position, Move) << std::endl;
                                    MoveCount++;
                                    break;
                                }
                                // Move
                                else
                                {
                                    std::cout <<  ConvertToAlgebraic(Piece, Position, Move)<< std::endl;
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

        // Convert a sqaure to algebraic notation
        std::string ToAlgebraicSquare(int Square){
            std::string output;
            switch (File(Square))
            {
                case 0:
                    output += "a";
                    break;
                case 1:
                    output += "b";
                    break;
                case 2:
                    output += "c";
                    break;
                case 3:
                    output += "d";
                    break;
                case 4:
                    output += "e";
                    break;
                case 5:
                    output += "f";
                    break;
                case 6:
                    output += "g";
                    break;
                case 7:
                    output += "h";
                    break;
                default:
                    output += " ";
                    break;
                };
                output += std::to_string(Row(Square) + 1);
                return output;
        }
        // Convert a move to algebraic notation
        char PieceToChar(int Piece, int Color)
        {
                char PieceChar;
                switch (Piece)
                {
                case Pawn:
                    PieceChar = 'P';
                    break;
                case Knight:
                    PieceChar = 'N';
                    break;
                case Bishop:
                    PieceChar = 'B';
                    break;
                case Rook:
                    PieceChar = 'R';
                    break;
                case Queen:
                    PieceChar = 'Q';
                    break;
                case King:
                    PieceChar = 'K';
                    break;
                default:
                    PieceChar = ' ';
                    break;
                };
                if (Color == White)
                {
                    PieceChar = toupper(PieceChar);
                }
                else if (Color == Black)
                {
                    PieceChar = tolower(PieceChar);
                }
                return PieceChar;
        }
        std::string ConvertToAlgebraic(int Piece, int Position, int Move)
        {   
            //Starting square (with) piece
            std::string AlgebricMove = "";
            if(Piece == Pawn)
            {
                AlgebricMove += ToAlgebraicSquare(Position);
            }
            else
            {
                AlgebricMove += PieceToChar(Piece, Color[Position]);
                AlgebricMove += ToAlgebraicSquare(Position);
            };
            //Move with capture
            if(Color[Move] == EnemySide)
            {
                AlgebricMove += "x";
                AlgebricMove += ToAlgebraicSquare(Move);
            };
            //Move without capture
            if(Color[Move] == Empty)
            {
                AlgebricMove += "-";
                AlgebricMove += ToAlgebraicSquare(Move);
            };
            return AlgebricMove;
        };
    };
};
