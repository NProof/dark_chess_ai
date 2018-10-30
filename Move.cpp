#include "Move.h"

Board::Move::Move(Board board, std::string strMove)
{
    originB = board;
    this->color = board.getTrun();
    this->strMove = strMove;
    this->iDark = 0;
    possibleKinds = std::map<char, int>();
    board.makeMove(strMove);
    this->possibleBoards[board] = 1;
}

Board::Move::Move(Board board, std::string strMove, int iDark, std::map<char, int> possibleChar)
{
    originB = board;
    this->color = board.getTrun();
    this->strMove = strMove+'-'+strMove;
    this->iDark = iDark;
    possibleKinds = possibleChar;
    possibleChar = board.getDarkPieces();
    for(std::map<char, int>::iterator it=possibleChar.begin(); it!=possibleChar.end(); it++)
    {
        Board possibleBoard(board);
        possibleBoard.makeMove(strMove+'('+it->first+')');
        this->possibleBoards[possibleBoard] = it->second;
    }
}

Board::Move::~Move()
{
    //dtor
}

bool Board::Move::operator<(const Move& other) const
{
	if(getStringMove()==other.getStringMove())
		return GetpossibleBoards()<other.GetpossibleBoards();
	return getStringMove()<other.getStringMove();
}

Board Board::Move::GetOringinB()
{
    return originB;
}

PROTO_CLR Board::Move::Getcolor() const
{
	return color;
}

std::string Board::Move::getStringMove() const
{
    return strMove;
}

int Board::Move::GetiDark() const
{
	return iDark;
}

std::map<char, int> Board::Move::GetpossibleKinds()
{
    return possibleKinds;
}

std::map<Board, int> Board::Move::GetpossibleBoards() const
{
	return possibleBoards;
}
