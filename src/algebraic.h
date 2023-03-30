#include <string>
#include "defs.h"
namespace CHAI
{
    namespace Algebraic
    {
        //Namespace for algebraic notation to CHAI-Int parsing
        int enemySide;
        int (**color)[64];
        // A function to set values
        void setGlobalValues(int (*colorArr)[64])
        {
            color = &colorArr;
        }
        // Convert a sqaure to algebraic notation
        std::string toAlgebraicSquare(int square)
        {
            std::string output;
            switch (file(square))
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
            output += std::to_string(row(square) + 1);
            return output;
        }
        // Convert a move to algebraic notation
        char pieceToChar(int piece, int color)
        {
            char pieceChar;
            switch (piece)
            {
            case pawn:
                pieceChar = 'P';
                break;
            case knight:
                pieceChar = 'N';
                break;
            case bishop:
                pieceChar = 'B';
                break;
            case rook:
                pieceChar = 'R';
                break;
            case queen:
                pieceChar = 'Q';
                break;
            case king:
                pieceChar = 'K';
                break;
            default:
                pieceChar = ' ';
                break;
            };
            if (color == white)
            {
                pieceChar = toupper(pieceChar);
            }
            else if (color == black)
            {
                pieceChar = tolower(pieceChar);
            }
            return pieceChar;
        }
        std::string convertToAlgebraic(int piece, int position, int move)
        {
            //Starting square (with) piece
            std::string algebricMove = "";
            if (piece == pawn)
            {
                algebricMove += toAlgebraicSquare(position);
            }
            else
            {
                algebricMove += pieceToChar(piece, (**color)[position]);
                algebricMove += toAlgebraicSquare(position);
            };
            //Move with capture
            if ((**color)[move] == enemySide)
            {
                algebricMove += "x";
                algebricMove += toAlgebraicSquare(move);
            }
            //Move without capture
            else if (color[move] == empty)
            {
                algebricMove += "-";
                algebricMove += toAlgebraicSquare(move);
            };
            return algebricMove;
        };
    }
}