#include <string>
#include "defs.h"
#include "position.h"
namespace Aurora
{
    namespace Algebraic
    {
        // Namespace for algebraic notation to Aurora-Int parsing
        Position *GameState;
        // A function to set values
        void setGlobalValues(Position &Position)
        {
            GameState = &Position;
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
            case PAWN:
                pieceChar = 'P';
                break;
            case KNIGHT:
                pieceChar = 'N';
                break;
            case BISHOP:
                pieceChar = 'B';
                break;
            case ROOK:
                pieceChar = 'R';
                break;
            case QUEEN:
                pieceChar = 'Q';
                break;
            case KING:
                pieceChar = 'K';
                break;
            default:
                pieceChar = ' ';
                break;
            };
            if (color == WHITE)
            {
                pieceChar = toupper(pieceChar);
            }
            else if (color == BLACK)
            {
                pieceChar = tolower(pieceChar);
            }
            return pieceChar;
        }
        std::string convertToAlgebraic(int position, int move)
        {
            // Starting square (with) piece
            std::string algebricMove = "";
            if (GameState->piece[position] == PAWN)
            {
                algebricMove += toAlgebraicSquare(position);
            }
            else
            {
                algebricMove += pieceToChar(GameState->piece[position], GameState->color[position]);
                algebricMove += toAlgebraicSquare(position);
            };
            // Move with capture
            if (GameState->color[move] == GameState->enemySide)
            {
                algebricMove += "x";
                algebricMove += toAlgebraicSquare(move);
            }
            // Move without capture
            else if (GameState->color[move] == EMPTY)
            {
                algebricMove += "-";
                algebricMove += toAlgebraicSquare(move);
            };
            return algebricMove;
        };
    }
}