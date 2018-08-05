#include "Score.h"

Score::Score()
{
	//ctor
}

Score::~Score()
{
	//dtor
}

Score::Score(const Score& other)
{
	//copy ctor
}

Score& Score::operator=(const Score& rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	//assignment operator
	return *this;
}

bool Score::operator<(const Score& other) const
{
	if(rateLose == other.rateLose)
	{
		if(rateWin == other.rateWin)
		{
			if(opWays == other.opWays)
			{
				if(myWays == other.myWays)
				{
					return false;
				}
				else myWays < other.myWays;
			}
			else opWays > other.opWays;
		}
		else return rateWin < other.rateWin;
	}
	else return rateLose > other.rateLose;
}

bool Score::maxScore()
{
	return rateWin==1.0;
}

bool Score::minScore()
{
	return rateLose==1.0;
}
