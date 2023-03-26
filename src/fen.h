
#include "defs.h"
#include <iostream>
#include <cctype>
// Main namespace of the CHAI chess engine
namespace CHAI
{
  // Namespace for FEN to CHAI-Int parsing
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
        color = white;
        if (fenChar == 'P')
        {
          type = pawn;
        }
        else if (fenChar == 'N')
        {
          type = knight;
        }
        else if (fenChar == 'B')
        {
          type = bishop;
        }
        else if (fenChar == 'R')
        {
          type = rook;
        }
        else if (fenChar == 'Q')
        {
          type = queen;
        }
        else if (fenChar == 'K')
        {
          type = king;
        }
      }
      else
      {
        color = black;
        if (fenChar == 'p')
        {
          type = pawn;
        }
        else if (fenChar == 'n')
        {
          type = knight;
        }
        else if (fenChar == 'b')
        {
          type = bishop;
        }
        else if (fenChar == 'r')
        {
          type = rook;
        }

        else if (fenChar == 'q')
        {
          type = queen;
        }
        else if (fenChar == 'k')
        {
          type = king;
        }
      };
      set(pieceArr, colorArr, pos, type, color);
    }
    // Convert FEN string to integral board data
    void parse(std::string fenString, int pieceArr[], int colorArr[])
    {
      std::cout << "Parsing...";
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
      std::cout << "Board State: \n";
      char output;
      for (int i = 0; i < 64;)
      {
        if (pieceArr[i] == empty)
        {
          output = '+';
        }
        else if (pieceArr[i] == pawn)
        {
          output = 'p';
        }
        else if (pieceArr[i] == knight)
        {
          output = 'n';
        }
        else if (pieceArr[i] == bishop)
        {
          output = 'b';
        }
        else if (pieceArr[i] == rook)
        {
          output = 'r';
        }
        else if (pieceArr[i] == queen)
        {
          output = 'q';
        }
        else if (pieceArr[i] == king)
        {
          output = 'k';
        }
        if (colorArr[i] == white)
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
