#include "Score.h"

Score::Score(int n_own, int n_opp, int n_method, int n_powers, int iDark)
{
    this->n_own = n_own;
    this->n_opp = n_opp;
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
    return Score(n_opp, n_own, -n_method, -n_powers, denominator);
}

bool Score::operator< (const Score other) const
{
    if(( n_method ) * other.denominator != ( other.n_method ) * denominator)
        return ( n_method ) * other.denominator < ( other.n_method ) * denominator;
    if( n_powers * (other.n_opp+1) * other.denominator != other.n_powers * (n_opp+1) * denominator)
        return n_powers * (other.n_opp+1) * other.denominator < other.n_powers * (n_opp+1) * denominator;
    return false;
}

bool Score::operator> (const Score other) const
{
    if(( n_method ) * other.denominator != ( other.n_method ) * denominator)
        return ( n_method ) * other.denominator > ( other.n_method ) * denominator;
    if( n_powers * (other.n_opp+1) * other.denominator != other.n_powers * (n_opp+1) * denominator)
        return n_powers * (other.n_opp+1) * other.denominator > other.n_powers * (n_opp+1) * denominator;
    return false;
}

Score & Score::operator+= (const Score & other)
{
    this->n_own += other.n_own;
    this->n_opp += other.n_opp;
    Setn_Method( Getn_Method() + other.Getn_Method());
    Setn_Powers( Getn_Powers() + other.Getn_Powers());
    return (*this);
}
Score & Score::operator*= (const int mul)
{
    this->n_own *= mul;
    this->n_opp *= mul;
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

const Score Score::minScore = Score(16,1,-64,-48,1);

const Score Score::maxScore = Score(1,16,64,48,1);
