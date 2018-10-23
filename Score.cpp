#include "Score.h"

Score::Score(Move mov)
{
	numerator = 0;
	powerchessman = 0;
	for(auto it : mov.GetpossibleBoards())
    {
        Board temp = it.first;
        numerator += (temp.getMoveValid().size()+temp.getSetCheckDark().size())*it.second;
        powerchessman += powerOfBoard(mov.Getcolor(), temp);
    }
    int iDark = mov.GetiDark();
	denominator = (iDark > 0) ? iDark : 1 ;
}

Score::~Score()
{
	//dtor
}

bool Score::operator<(const Score other) const
{
    return ( 5 * numerator + powerchessman ) * other.denominator
        < ( 5 * other.numerator + other.powerchessman ) * denominator;
}

int Score::powerOfBoard(bool color, Board board)
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
    return color ? -val : val;
}
