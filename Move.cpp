#include "Move.h"

Move::Move(Board * srcBoard, std::string srcMove, std::string dstMove)
{
    this->srcBoard = srcBoard;
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

std::string Move::getSrcMove()
{
    return srcMove;
}

std::string Move::getDstMove()
{
    return dstMove;
}
