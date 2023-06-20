
#include "defs.h"
#include <iostream>
#include <cctype>
// Main namespace of the Aurora chess engine
namespace Aurora
{
  // Namespace for FEN to Aurora-Int parsing
  namespace FEN
  {
    // A function to set values
    void set(int pieceArr[], int colorArr[], int pos, int type, int color)
    {
      pieceArr[pos] = type;
      colorArr[pos] = color;
    };
    // Convert FEN characters to integers
    void pieceParse(char fenChar, int pieceArr[], int colorArr[], int pos)
    {
      int type;
      int color;
      if (isupper(fenChar))
      {
        color = WHITE;
        if (fenChar == 'P')
        {
          type = PAWN;
        }
        else if (fenChar == 'N')
        {
          type = KNIGHT;
        }
        else if (fenChar == 'B')
        {
          type = BISHOP;
        }
        else if (fenChar == 'R')
        {
          type = ROOK;
        }
        else if (fenChar == 'Q')
        {
          type = QUEEN;
        }
        else if (fenChar == 'K')
        {
          type = KING;
        }
      }
      else
      {
        color = BLACK;
        if (fenChar == 'p')
        {
          type = PAWN;
        }
        else if (fenChar == 'n')
        {
          type = KNIGHT;
        }
        else if (fenChar == 'b')
        {
          type = BISHOP;
        }
        else if (fenChar == 'r')
        {
          type = ROOK;
        }

        else if (fenChar == 'q')
        {
          type = QUEEN;
        }
        else if (fenChar == 'k')
        {
          type = KING;
        }
      };
      set(pieceArr, colorArr, pos, type, color);
    }
    // Convert FEN string to integral board data
    void parse(std::string fenString, int pieceArr[], int colorArr[])
    {
      std::cout << "PARSING...";
      // Loop through string
      int currentSquare = 0;
      for (int i = 0; i < fenString.length();)
      {
        // If it is a piece
        if (isalpha(fenString[i]))
        {
          pieceParse(fenString[i], pieceArr, colorArr, currentSquare);
          currentSquare++;
          i++;
        }
        // If it is a digit
        else if (isdigit(fenString[i]))
        {
          // Add the digit to the current square
          currentSquare += int(fenString[i] - '0');
          i++;
        }
        else if (fenString[i] == '/')
        {
          i++;
        }
      };
    };
    // Display the board state to a terminal
    void displayBoard(int pieceArr[], int colorArr[])
    {
      std::cout << "BOARD STATE: \n";
      char output;
      for (int i = 0; i < 64;)
      {
        if (pieceArr[i] == EMPTY)
        {
          output = '+';
        }
        else if (pieceArr[i] == PAWN)
        {
          output = 'p';
        }
        else if (pieceArr[i] == KNIGHT)
        {
          output = 'n';
        }
        else if (pieceArr[i] == BISHOP)
        {
          output = 'b';
        }
        else if (pieceArr[i] == ROOK)
        {
          output = 'r';
        }
        else if (pieceArr[i] == QUEEN)
        {
          output = 'q';
        }
        else if (pieceArr[i] == KING)
        {
          output = 'k';
        }
        if (colorArr[i] == WHITE)
        {
          output = toupper(output);
        };
        // Make a new line if already eight charcters were printed in the current one
        if (i % 8 == 0)
        {
          std::cout << std::endl;
        };
        std::cout << output << " ";
        i++;
      }
    };
  }
}
