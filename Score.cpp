#include "Score.h"

Score::Score(double win, double draw, double lose)
{
    this->win = win;
    this->draw = draw;
    this->lose = lose;
}

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
    SetWin( GetWin() + other.GetWin());
    SetDraw( GetDraw() + other.GetDraw());
    SetLose( GetLose() + other.GetLose());
    Setn_Method( Getn_Method() + other.Getn_Method());
    Setn_Powers( Getn_Powers() + other.Getn_Powers());
}
Score & Score::operator*= (const int mul)
{
    SetWin(win * mul);
    SetDraw(draw * mul);
    SetLose(lose * mul);
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
