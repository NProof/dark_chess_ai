#include "Score.h"

Score::Score(Move move)
{
	numerator = 0;
	for(auto it : move.GetpossibleBoards())
    {
        Board temp = it.first;
        numerator += (temp.getMoveValid(!move.Getcolor()).size()+temp.getSetCheckDark().size())*it.second;
    }
	denominator = move.GetiDark();
}

Score::~Score()
{
	//dtor
}

bool Score::operator<(const Score other) const
{
	int scorei = numerator, scorej = other.numerator;
	if(denominator>1)
        scorej *= denominator;
    if(other.denominator>1)
        scorei *= other.denominator;
	return scorei<scorej;
}
