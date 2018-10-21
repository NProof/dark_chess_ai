#include "Score.h"

Score::Score(Move move)
{
	numerator = 0;
	for(auto it : move.GetpossibleBoards())
    {
        Board temp = it.first;
        numerator += (temp.getMoveValid(!move.Getcolor()).size()+temp.getSetCheckDark().size())*it.second;
    }
    int iDark = move.GetiDark();
	denominator = (iDark > 0) ? iDark : 1 ;
}

Score::~Score()
{
	//dtor
}

bool Score::operator<(const Score other) const
{
	return numerator * other.denominator < other.numerator * denominator;
}
