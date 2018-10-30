#include "Move.h"

Board::Move::Move(Board board, std::string strMove)
{
    this->color = board.getTrun();
    this->strMove = strMove;
    this->iDark = 0;
    board.makeMove(strMove);
    this->possibleBoards[board] = 1;
}

Board::Move::Move(Board board, std::string strMove, int iDark, std::map<char, int> possibleChar)
{
    this->color = board.getTrun();
    this->strMove = strMove+'-'+strMove;
    this->iDark = iDark;
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

std::map<Board, int> Board::Move::GetpossibleBoards() const
{
	return possibleBoards;
}
