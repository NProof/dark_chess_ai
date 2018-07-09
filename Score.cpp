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
            return false;
        }
        else return rateWin < other.rateWin;
    }
    else return rateLose > other.rateLose;
}
