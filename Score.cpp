#include "Score.h"

Score::Score(int n_method, int n_powers, int iDark)
{
    Setn_Method(n_method);
    Setn_Powers(n_powers);
    Setdenominator(iDark);
}

Score::~Score()
{
	//dtor
}

Score Score::operator- () const
{
    return Score(-n_method, -n_powers, denominator);
}

bool Score::operator< (const Score other) const
{
    return ( n_method ) * other.denominator
        < ( other.n_method ) * denominator;
}

bool Score::operator> (const Score other) const
{
    return ( n_method ) * other.denominator
        > ( other.n_method ) * denominator;
}

Score & Score::operator+= (const Score & other)
{
    Setn_Method( Getn_Method() + other.Getn_Method());
    Setn_Powers( Getn_Powers() + other.Getn_Powers());
    return (*this);
}
Score & Score::operator*= (const int mul)
{
    Setn_Method(n_method * mul);
    Setn_Powers(n_powers * mul);
    Setdenominator(denominator * mul);
    return (*this);
}
Score & Score::operator/= (const int div)
{
    if(div > 1){
        Setdenominator(denominator * div);
    }
    return (*this);
}

const Score Score::minScore = Score(0.0 ,0.0 ,DBL_MAX);
