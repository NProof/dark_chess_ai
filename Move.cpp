#include "Move.h"

Board::Move::Move(Board board, std::string strMove)
{
    originB = board;
    this->strMove = strMove;
    this->iDark = 0;
    possibleKinds = std::map<char, int>();
    board.makeMove(strMove);
    possibleBoards[board] = 1;
}

Board::Move::Move(Board board, std::string strMove, int iDark, std::map<char, int> possibleChar)
{
    originB = board;
    this->strMove = strMove+'-'+strMove;
    this->iDark = iDark;
    possibleKinds = possibleChar;
    std::string strPos = strMove.substr(0,2);
    for(std::map<char, int>::iterator it=possibleKinds.begin(); it!=possibleKinds.end(); it++)
    {
        Board possibleBoard(board);
        possibleBoard.makeMove(strPos+'('+it->first+')');
        possibleBoards[possibleBoard] = it->second;
    }
}

Board::Move::~Move()
{
    //dtor
}

bool Board::Move::operator<(const Move& other) const
{
	if(iDark != other.iDark)
        return iDark < other.iDark;
    if(possibleKinds != other.possibleKinds)
        return possibleKinds < other.possibleKinds;
    if(originB != other.originB)
        return originB < other.originB;
    return strMove < other.strMove;
}

Board Board::Move::GetOringinB()
{
    return originB;
}

std::string Board::Move::getStringMove()
{
    return strMove;
}

int Board::Move::GetiDark()
{
	return iDark;
}

std::map<char, int> Board::Move::GetpossibleKinds()
{
    return possibleKinds;
}

std::map<Board, int> Board::Move::GetpossibleBoards()
{
    return possibleBoards;
}
