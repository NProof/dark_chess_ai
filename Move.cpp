#include "Move.h"

Move::Move(Board * srcBoard, bool color, std::string srcMove, std::string dstMove)
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

Board * Move::getSrcBoard()
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
