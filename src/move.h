
namespace CHAI
{
    class Move
    {
    public:
        int from;
        int to;
        // Flags
        bool *isCapture;
        bool *isPromotion;
        bool *isEnPassant;
        bool *isCastle;
        bool *isQCastle;
        // Promotion
        int promotionPiece;
        Move(int from, int to, bool isCapture = false, bool isPromotion = false, bool isEnPassant = false, bool isCastle = false, bool isQCastle = false, int promotionPiece = 0)
        {
            //Set values from parameters
            int from = this->from;
            int to = this->to;
            bool isCapture = this->isCapture;
            bool isPromotion = this->isPromotion;
            bool isEnPassant = this->isEnPassant;
            bool IsCastle = this->isCastle;
            bool IsQCastle = this->isQCastle;
            int PromotionPiece = this->promotionPiece;
        };
    };
};