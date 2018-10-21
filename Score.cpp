#include "Score.h"

Score::Score(Move mov)
{
	numerator = 0;
	for(auto it : mov.GetpossibleBoards())
    {
        Board temp = it.first;
        numerator += (temp.getMoveValid(!mov.Getcolor()).size()+temp.getSetCheckDark().size())*it.second;
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
