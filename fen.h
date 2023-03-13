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
    void Set(int *PieceArr, int *ColorArr, int Pos, int Type, int Color)
    {
      PieceArr[Pos] = Type;
      ColorArr[Pos] = Color;
    };
    // Convert FEN characters to integers
    void PieceParse(char FenChar, int *PieceArr, int *ColorArr, int Pos)
    {
      int Type;
      int Color;
      if (isupper(FenChar))
      {
        Color = White;
        if (FenChar == 'P')
        {
          Type = Pawn;
        }
        else if (FenChar == 'N')
        {
          Type = Knight;
        }
        else if (FenChar == 'B')
        {
          Type = Bishop;
        }
        else if (FenChar == 'R')
        {
          Type = Rook;
        }
        else if (FenChar == 'Q')
        {
          Type = Queen;
        }
        else if (FenChar == 'K')
        {
          Type = King;
        }
      }
      else
      {
        Color = Black;
        if (FenChar == 'p')
        {
          Type = Pawn;
        }
        else if (FenChar == 'n')
        {
          Type = Knight;
        }
        else if (FenChar == 'b')
        {
          Type = Bishop;
        }
        else if (FenChar == 'r')
        {
          Type = Rook;
        }

        else if (FenChar == 'q')
        {
          Type = Queen;
        }
        else if (FenChar == 'k')
        {
          Type = King;
        }
      };
      Set(PieceArr, ColorArr, Pos, Type, Color);
    }
    // Convert FEN string to integral board data
    void Parse(std::string FenString, int *PieceArr, int *ColorArr)
    {
      std::cout << "Parsing...";
      // Loop through string
      int CurrentSquare = 0;
      for (int i = 0; i < FenString.length();)
      {
        // If it is a piece
        if (isalpha(FenString[i]))
        {
          PieceParse(FenString[i], PieceArr, ColorArr, CurrentSquare);
          CurrentSquare++;
          i++;
        }
        // If it is a digit
        else if (isdigit(FenString[i]))
        {
          // Add the digit to the current square
          CurrentSquare += int(FenString[i] - '0');
          i++;
        }
        else if (FenString[i] == '/')
        {
          i++;
        }
      };
    };
    // Display the board state to a terminal
    void DisplayBoard(int *Piece, int *Color)
    {
      std::cout << "Board State: \n";
      char output;
      for (int i = 0; i < 64;)
      {
        if (Piece[i] == Empty)
        {
          output = '+';
        }
        else if (Piece[i] == Pawn)
        {
          output = 'p';
        }
        else if (Piece[i] == Knight)
        {
          output = 'n';
        }
        else if (Piece[i] == Bishop)
        {
          output = 'b';
        }
        else if (Piece[i] == Rook)
        {
          output = 'r';
        }
        else if (Piece[i] == Queen)
        {
          output = 'q';
        }
        else if (Piece[i] == King)
        {
          output = 'k';
        }
        if (Color[i] == White)
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
