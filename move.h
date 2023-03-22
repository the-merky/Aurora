
namespace CHAI
{
    class Move
    {
        int From;
        int To;
        // Flags
        bool *IsCapture;
        bool *IsPromotion;
        bool *IsEnPassant;
        bool *IsCastle;
        bool *IsQCastle;
        // Promotion
        int PromotionPiece;
        Move(int From, int To, bool IsCapture = false, bool IsPromotion = false, bool IsEnPassant = false, bool IsCastle = false, bool IsQCastle = false, int PromotionPiece = 0)
        {
            //Set values from parameters
            int From = this->From;
            int To = this->To;
            bool IsCapture = this->IsCapture;
            bool IsPromotion = this->IsPromotion;
            bool IsEnPassant = this->IsEnPassant;
            bool IsCastle = this->IsCastle;
            bool IsQCastle = this->IsQCastle;
            int PromotionPiece = this->PromotionPiece;
        };
    };
};