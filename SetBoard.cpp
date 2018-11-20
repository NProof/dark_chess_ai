#include "SetBoard.h"

SetBoard::SetBoard(Board board, std::string strMove)
{
	this->strMove = strMove;
	this->iDark = 0;
	board.makeMove(strMove);
	possibleBoards[board] = 1;
}

SetBoard::SetBoard(Board board, std::string strMove, int iDark, std::map<char, int> possibleChar)
{
	this->strMove = strMove+'-'+strMove;
	this->iDark = iDark;
	std::string strPos = strMove.substr(0,2);
	for(std::map<char, int>::iterator it=possibleChar.begin(); it!=possibleChar.end(); it++)
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
	if(strMove != other.strMove)
		return strMove < other.strMove;
	return possibleBoards < other.possibleBoards;
}

int SetBoard::GetiDark()
{
	return iDark;
}

std::map<Board, int> SetBoard::GetpossibleBoards()
{
	return possibleBoards;
}
