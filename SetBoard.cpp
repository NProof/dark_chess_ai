#include "SetBoard.h"

SetBoard::SetBoard(Board board, std::string strMove)
{
	originB = board;
	this->strMove = strMove;
	this->iDark = 0;
	possibleKinds = std::map<char, int>();
	board.makeMove(strMove);
	possibleBoards[board] = 1;
}

SetBoard::SetBoard(Board board, std::string strMove, int iDark, std::map<char, int> possibleChar)
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

SetBoard::~SetBoard()
{
	//dtor
}

bool SetBoard::operator<(const SetBoard& other) const
{
	if(iDark != other.iDark)
		return iDark < other.iDark;
	if(possibleKinds != other.possibleKinds)
		return possibleKinds < other.possibleKinds;
	if(originB != other.originB)
		return originB < other.originB;
	return strMove < other.strMove;
}

Board SetBoard::GetOringinB()
{
	return originB;
}

std::string SetBoard::getStringMove()
{
	return strMove;
}

int SetBoard::GetiDark()
{
	return iDark;
}

std::map<char, int> SetBoard::GetpossibleKinds()
{
	return possibleKinds;
}

std::map<Board, int> SetBoard::GetpossibleBoards()
{
	return possibleBoards;
}
