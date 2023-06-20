#include <vector>
#include "move.h"
namespace Aurora
{
    class Position
    {
    public:
        std::vector<Move> moves;
        int color[64] = {};
        int piece[64] = {};
        int enemySide;
        bool bQCastlingRights;
        bool bKCastlingRights;
        bool wQCastlingRights;
        bool wKCastlingRights;
        Position(int side)
        {
            enemySide = (side == WHITE) ? BLACK : WHITE;
        }
    };
};