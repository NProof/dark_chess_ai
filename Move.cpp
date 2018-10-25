#include "Move.h"

Move::Move(Board board, std::string strMove)
{
    this->color = board.getTrun();
    this->strMove = strMove;
    this->iDark = 0;
    board.makeMove(strMove);
    this->possibleBoards[board] = 1;
}

Move::Move(Board board, std::string strMove, int iDark, std::map<char, int> possibleChar)
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

Move::~Move()
{
    //dtor
}

bool Move::operator<(const Move& other) const
{
	if(getStringMove()==other.getStringMove())
		return GetpossibleBoards()<other.GetpossibleBoards();
	return getStringMove()<other.getStringMove();
}

Score * Move::Getscore()
{
	if(score == NULL)
		// const_cast<Move *>(this)->score = new Score(*this);
		this->score = new Score(*this);
	return score;
}

bool Move::Getcolor() const
{
	return color;
}

std::string Move::getStringMove() const
{
    return strMove;
}

int Move::GetiDark() const
{
	return iDark;
}

std::map<Board, int> Move::GetpossibleBoards() const
{
	return possibleBoards;
}
