#include "Score.h"

Score::Score()
{
	rateWin = 0.0;
	myWays = 0;
	rateDraw = 0.0;
	opWays = 0;
	rateLose = 0.0;
}

Score::~Score()
{
	//dtor
}

Score::Score(const Score& other)
{
	//copy ctor
	this->rateWin = other.rateWin;
	this->myWays = other.myWays;
	this->rateDraw = other.rateDraw;
	this->opWays = other.opWays;
	this->rateLose = other.rateLose;
}

Score& Score::operator=(const Score& rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	//assignment operator
	this->rateWin = rhs.rateWin;
	this->myWays = rhs.myWays;
	this->rateDraw = rhs.rateDraw;
	this->opWays = rhs.opWays;
	this->rateLose = rhs.rateLose;
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
