
#include <vector>
namespace CHAI
{
    class Position
    {
    public:
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