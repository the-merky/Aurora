
#include <array>
namespace CHAI
{
    class Position
    {
    public:
        int Color[64] = {};
        int Piece[64] = {};
        bool BQCastlingRights;
        bool BKCastlingRights;
        bool WQCastlingRights;
        bool WKCastlingRights;
    };
};