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

bool Score::operator<(const Score other) const
{
    return ( n_method ) * other.denominator
        < ( other.n_method ) * denominator;
}

bool Score::operator>(const Score other) const
{
    return ( n_method ) * other.denominator
        > ( other.n_method ) * denominator;
}

void Score::operator+=(const Score other)
{
    SetWin( GetWin() + other.GetWin());
    SetDraw( GetDraw() + other.GetDraw());
    SetLose( GetLose() + other.GetLose());
    Setn_Method( Getn_Method() + other.Getn_Method());
    Setn_Powers( Getn_Powers() + other.Getn_Powers());
}

Score Score::operator *(int mul) const
{
    Score score(*this);
    score.SetWin(win * mul);
    score.SetDraw(draw * mul);
    score.SetLose(lose * mul);
    score.Setn_Method(n_method * mul);
    score.Setn_Powers(n_powers * mul);
    score.Setdenominator(denominator * mul);
    return score;
}

Score Score::operator /(int div) const
{
    Score score(*this);
    if(div > 1){
        score.Setdenominator(denominator * div);
    }
    return score;
}

const Score Score::minScore = Score(0.0 ,0.0 ,DBL_MAX);
