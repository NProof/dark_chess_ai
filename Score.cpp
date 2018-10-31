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

bool Score::operator<(const Score other) const
{
    return ( 5 * n_method + n_powers ) * other.denominator
        < ( 5 * other.n_method + other.n_powers ) * denominator;
}

int Score::method(Board board)
{
    return board.getMoveValid().size() + board.getSetCheckDark().size();
}

int Score::powers(Board board)
{
    auto light = board.getLightPieces();
    auto dark = board.getDarkPieces();
    for(auto x : dark){
        light[x.first] += x.second;
    }
    int val =
    (
        light['k']*(light['G']+light['M']+light['R']+light['N']+light['C']-light['P'])
        +light['g']*(light['M']+light['R']+light['N']+light['C']+light['P']-light['K'])
        +light['m']*(light['R']+light['N']+light['C']+light['P']-light['K']-light['G'])
        +light['r']*(light['N']+light['C']+light['P']-light['K']-light['G']-light['M'])
        +light['n']*(light['C']+light['P']-light['K']-light['G']-light['M']-light['R'])
        +light['c']*(light['P']) // -light['K']-light['G']-light['M']-light['R']-light['N'])
        +light['p']*(light['K']-light['G']-light['M']-light['R']-light['N']-light['C'])
    );
    switch(board.getTrun()){
    case PROTO_CLR::PCLR_RED:
        return val;
    case PROTO_CLR::PCLR_BLACK:
        return val;
    default:
        exit(25);
    };
}
