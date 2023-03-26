
#include <array>
namespace CHAI
{
    class Position
    {
    public:
        int color[64] = {};
        int piece[64] = {};
        bool bQCastlingRights;
        bool bKCastlingRights;
        bool wQCastlingRights;
        bool wKCastlingRights;
    };
};