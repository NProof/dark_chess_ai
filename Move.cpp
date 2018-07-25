#include "Move.h"

Move::Move(Board srcBoard, bool color, std::string srcMove, std::string dstMove)
{
	this->srcBoard = srcBoard;
	this->color = color;
	this->srcMove = srcMove;
	this->dstMove = dstMove;
}

Move::~Move()
{
	//dtor
}

bool Move::operator<(const Move& other) const
{
	if(this->color == other.color)
	{
		if(srcBoard < other.srcBoard)
		{
			return true;
		}
		else if(other.srcBoard < srcBoard)
		{
			return false;
		}
		else
		{
			if(this->srcMove == other.srcMove)
			{
				if(this->dstMove == other.dstMove)
				{
					return false;
				}
				else return dstMove < other.dstMove;
			}
			else return srcMove < other.srcMove;
		}
	}
	else return color < other.color;
}

Board Move::getSrcBoard()
{
	return srcBoard;
}

bool Move::getColor()
{
	return color;
}

std::string Move::getSrcMove()
{
	return srcMove;
}

std::string Move::getDstMove()
{
	return dstMove;
}
