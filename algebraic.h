#include <string>
#include "defs.h"
namespace CHAI
{
    namespace Algebraic
    {
        //Namespace for algebraic notation to CHAI-Int parsing
        int EnemySide;
        int *Color;
        // A function to set values
        void SetGlobalValues(int Side, int ColorArr[])
        {
            EnemySide = (Side == White) ? Black : White;
            Color = ColorArr;
        }
        // Convert a sqaure to algebraic notation
        std::string ToAlgebraicSquare(int Square)
        {
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
            if (Piece == Pawn)
            {
                AlgebricMove += ToAlgebraicSquare(Position);
            }
            else
            {
                AlgebricMove += PieceToChar(Piece, Color[Position]);
                AlgebricMove += ToAlgebraicSquare(Position);
            };
            //Move with capture
            if (Color[Move] == EnemySide)
            {
                AlgebricMove += "x";
                AlgebricMove += ToAlgebraicSquare(Move);
            }
            //Move without capture
            else if (Color[Move] == Empty)
            {
                AlgebricMove += "-";
                AlgebricMove += ToAlgebraicSquare(Move);
            };
            return AlgebricMove;
        };
    }
}