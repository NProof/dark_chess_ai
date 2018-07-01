#include "Move.h"

Move::Move(bool color, Board board, std::string strMove)
{
    this->color = color;
    this->strMove = strMove;
    this->iDark = 0;
    board.makeMove(strMove);
    this->possibleBoards[board] = 1;
}

Move::Move(bool color, Board board, std::string strMove, int iDark, std::map<char, int> possibleChar)
{
    this->color = color;
    this->strMove = strMove+'-'+strMove;
    this->iDark = iDark;
    for(std::map<char, int>::iterator it=possibleChar.begin(); it!=possibleChar.end(); it++)
    {
        Board possibleBoard(board);
        possibleBoard.makeMove(strMove+'('+it->first+')');
        this->possibleBoards[possibleBoard] = it->second;
    }
}

Move::~Move()
{
    //dtor
}

bool Move::operator<(const Move& other) const
{
    int i = 0, j = 0;
    for(auto it : possibleBoards)
    {
        Board temp = it.first;
        i += (temp.getMoveValid(!color).size()+temp.getSetCheckDark().size())*it.second;
    }
    for(auto it : other.possibleBoards)
    {
        Board temp = it.first;
        j += (temp.getMoveValid(!color).size()+temp.getSetCheckDark().size())*it.second;
    }
    if(iDark>1)
        j *= iDark;
    if(other.iDark>1)
        i *= other.iDark;
    return i < j;
}

std::string Move::getStringMove() const
{
    return strMove;
}
